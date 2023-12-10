-- Old mouse positions
local old_mouse_positions = {}
for controller_index=1, mouse.maximalControllerCount do
    table.insert(old_mouse_positions, { x = 0, y = 0 })
end

-- Skip frames
local skip_frames = 2

-- Break force
local break_force = 100

-- Current frame
local current_frame = 0

-- Initialize event
events.registerEvent(
    'init',
    function()
        for controller_index=1, mouse.maximalControllerCount do
            local x, y = mouse.getCursorPosition(controller_index)
            old_mouse_positions[controller_index].x = x
            old_mouse_positions[controller_index].y = y
        end
	    print('========================')
	    print('=                      =')
	    print('=     Slippy mouse     =')
	    print('=                      =')
	    print('=  Made by Ethem Kurt  =')
	    print('=                      =')
	    print('========================')
    end
)

-- Tick event
events.registerEvent(
    'tick',
    function()
        for controller_index=1, mouse.maximalControllerCount do
            local x, y = mouse.getCursorPosition(controller_index)
            local delta_x = x - old_mouse_positions[controller_index].x
            local delta_y = y - old_mouse_positions[controller_index].y
            current_frame = current_frame + 1
            if (current_frame % skip_frames) == 0 then
                if delta_x > (break_force - 1) then
                    delta_x = delta_x - break_force
                elseif delta_x < -(break_force - 1) then
                    delta_x = delta_x + break_force
                else
                    delta_x = 0
                end
                if delta_y > (break_force - 1) then
                    delta_y = delta_y - break_force
                elseif delta_y < -(break_force - 1) then
                    delta_y = delta_y + break_force
                else
                    delta_y = 0
                end
                current_frame = 0;
            end
            if (math.abs(delta_x) > 0) or math.abs(delta_y) > 0 then
                mouse.moveCursor(controller_index, delta_x, delta_y)
            end
            old_mouse_positions[controller_index].x = x
            old_mouse_positions[controller_index].y = y
        end
    end
)
