Creating a New Release
======================

In principle, creating a release is nothing more than adding a version
tag for a particular commit. In practice, we want to provide more:

1. Functional (tested) software for multiple configurations with all
   our packages, especially those not automatically covered by CI.

2. Consistent and relevant documentation, including:
   - up-to-date reference documentation
   - a detailed changelog
   - a release news article

This document serves as a guide. Consider ``X.Y.Z`` to be the version
about to be released, and ``A.B.C`` as the previous version that was
released.

.. highlight:: bash

Update Github Milestone
-----------------------

1. There should be a `milestone <https://github.com/eclipse/cloe/milestones>`_
   named the precise version ``X.Y.Z`` that shall be released.

   All issues and pull requests that should be merged for this release should be
   assigned to this milestone. All pull requests that were merged to the main
   branch since the last release should have been assigned to this milestone.
   `Check <https://github.com/eclipse/cloe/pulls?q=is%3Apr+is%3Amerged+no%3Amilestone>`_
   to make sure that this is the case.

   This makes it easy to see at a glance what is in and what is not in a release.
   It's best to plan for the next few releases in advance if possible, and
   assign PRs and issues to milestones even before they are merged or closed.

2. Ensure that there are no more open PRs or issues assigned to the milestone.

   Either move them to another milestone or remove the milestone from the issue
   and pull request.

3. Create a new branch from master ``release/X.Y.0`` and switch to it in your
   development environment.

   Feel free to create a draft pull request from this branch if you want early
   feedback. Assign this pull request to the milestone.

Build Conan Packages
--------------------

First, set the ``VERSION`` file to ``X.Y.Z``::

    echo "X.Y.Z" > VERSION

This is fudging the version in order to generate better documentation, so we
need to be careful to remove this before actually making a release.

Then, compile the entire project locally::

    make purge-all export-vendor export smoketest-deps smoketest

This should run through without errors. Then make sure to do the same with
the optional packages::

    make -C optional/vtd export-vendor export smoketest-deps smoketest

We will not be releasing these packages, they are used for documentation
generation.

Update the Documentation
------------------------

Places in the documentation which require attention at every release have
a ``TODO(release)`` comment which explains what needs to be done.
Search for those with your editor!

This includes the documentation for the following steps:

1. Generate the plugin documentation
2. Update the changelog
3. Write a release news article

Bump Versions Strings
---------------------

For now we are releasing all parts of Cloe in lock-step, even though they
are separate packages sometimes.

1. Update cloe-launch version in ``cli/pyproject.yaml``.
   Run ``dephell`` afterwards to update ``cli/setup.py``, or if you are confident
   only the version has changed, do it yourself.

2. Update smoketest conanfiles requires to ``cloe-launch-profile``, if necessary.
   It's ok for them to depend on older versions, if they are still compatible.

3. Update Web UI version in ``ui/package.json``.

Since we can't cover everything, search the project for Cloe version strings to
check for examples and configurations that are rendered outdated by the version
update. For example, if updating from ``0.19.0`` to ``0.20.0``, then use a tool
like ripgrep to search the project for strings containing ``0.19``.

.. note::
   Don't just willy nilly update each string to the next version though. If
   there is example output, it may be better to just leave it as is, unless we
   expect the content to signficantly change, in which case we should regenerate
   the example output.
