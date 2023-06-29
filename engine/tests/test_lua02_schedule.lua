-- This example shows that you don't actually need any plugins at
-- all to have a simulation. You can simple schedule some tasks.
local cloe = require("cloe")

cloe.log("info", "Hello world!");

cloe.schedule {
    on = "loop",
    priority = 101, -- higher than the default
    pin = false,
    run = function(_)
        cloe.log("info", "Hello world!")
    end
}

cloe.schedule {
    on = "loop",
    pin = true,
    run = function(sync)
        cloe.log("info", "Current time is %s", sync:time())
    end
}

-- If you configure this to terminate at for example, 60 seconds,
-- you may notice that we don't even achieve realtime. This is
-- because of the server. See the next test file.
local seconds = 1
cloe.schedule {
    on = "time=" .. seconds,
    run = "succeed"
}
