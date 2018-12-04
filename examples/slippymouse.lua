-- Old mouse X
local oldX = 0

-- Old mouse Y
local oldY = 0

-- Skip frames
local skipFrames = 20

-- Current frame
local currentFrame = 0

-- Init event
event.register('init', function()
    local x, y = mouse.getPosition()
    oldX = x
    oldY = y
	print('==================')
	print('=  Slippy mouse  =')
	print('= Made by BigETI =')
	print('==================')
end)

-- Tick event
event.register('tick', function()
    local x, y = mouse.getPosition()
    local delta_x = x - oldX
    local delta_y = y - oldY
    currentFrame = currentFrame + 1
    if (currentFrame % skipFrames) == 0 then
        if delta_x > 0 then
            delta_x = delta_x - 1
        elseif delta_x < 0 then
            delta_x = delta_x + 1
        end
        if delta_y > 0 then
            delta_y = delta_y - 1
        elseif delta_y < 0 then
            delta_y = delta_y + 1
        end
        currentFrame = 0;
    end
    mouse.move(delta_x, delta_y)
    oldX = x
    oldY = y
end)
