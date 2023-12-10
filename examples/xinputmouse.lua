-- Clamps the specified value to the specified range
function clamp(value, minimum, maximum)
	return math.max(math.min(value, maximum), minimum)
end

-- Creates a new mouse button controller
function createMouseButtonController(mouseButtonID)
	local ret = { id = mouseButtonID, isPressing = false }
	function ret:press(isPressing)
		if (type(isPressing) == 'boolean') and not (self.isPressing == isPressing) then
			self.isPressing = isPressing
			if isPressing then
				mouse.pressButton(1, self.id, isPressing)
			else
				mouse.releaseButton(1, self.id, isPressing)
			end
		end
	end
	return ret
end

-- Creates a new application launcher
function createApplicationLauncher(applicationPath)
	if not (type(applicationPath) == 'string') then
		return nil
	end
	local ret = { applicationPath = applicationPath }
	function ret.launch()
		os.execute(ret.applicationPath)
	end
	return ret
end

-- Mouse speed
local maximal_mouse_speed = 64

-- Scroll speed
local maximal_scroll_speed = 64

local deadzone = 0.03125 * 0.5

--local two_squared = 1
local two_squared = math.sqrt(2)

-- Left mouse button controller
local left_mouse_button_controller = createMouseButtonController(mouse.left)

-- Right mouse button controller
local right_mouse_button_controller = createMouseButtonController(mouse.right)

-- Is app button down
local is_launching_application_button_down = false

-- Available applications
local up_application = createApplicationLauncher('start osk.exe')
local down_application = createApplicationLauncher('explorer.exe')
local left_application = createApplicationLauncher('start mspaint.exe')
local right_application = createApplicationLauncher('calc.exe')

-- Initialize event
events.registerEvent(
	'init',
	function()
		print('========================')
		print('=                      =')
		print('=     XInput mouse     =')
		print('=                      =')
		print('=  Made by Ethem Kurt  =')
		print('=                      =')
		print('========================')
	end
)

-- Tick Event
events.registerEvent(
	'tick',
	function()
		local exit_combination = xinput.start | xinput.back | xinput.leftShoulder | xinput.rightShoulder
		for controller_index=1, xinput.maximalControllerCount do
			if xinput.isConnected(controller_index) then
				local buttons = xinput.getPressedButtons(controller_index)
				if (buttons & exit_combination) == exit_combination then
					runtime.exit()
				end
				local x = xinput.getAxisValue(controller_index, xinput.thumbLX) * two_squared
				x = clamp(math.abs(x) * x, -1.0, 1.0)
				local y = xinput.getAxisValue(controller_index, xinput.thumbLY) * two_squared
				y = clamp(math.abs(y) * y, -1.0, 1.0)
				local xy_magnitude_squared = (x * x) + (y * y);
				if xy_magnitude_squared > 1.0 then
					local xy_magnitude = math.sqrt(xy_magnitude_squared)
					x = x / xy_magnitude;
					y = y / xy_magnitude;
				end
				local s = xinput.getAxisValue(controller_index, xinput.thumbRY)
				s = clamp(math.abs(s) * s, -1.0, 1.0)
				if (math.abs(x) > deadzone) or (math.abs(y) > deadzone) then
					mouse.moveCursor(1, math.floor(x * maximal_mouse_speed), -math.floor(y * maximal_mouse_speed))
				end
				if math.abs(s) > deadzone then
					mouse.scrollWheel(1, math.floor(s * maximal_scroll_speed))
				end
				left_mouse_button_controller:press((buttons & (xinput.leftThumb | xinput.a | xinput.b)) > 0)
				right_mouse_button_controller:press((buttons & (xinput.rightThumb | xinput.x | xinput.y)) > 0)
				if (buttons & (xinput.dPadUp | xinput.dPadDown | xinput.dPadLeft | xinput.dPadRight)) > 0 then
					if not is_launching_application_button_down then
						is_launching_application_button_down = true
						if (buttons & xinput.dPadUp) == xinput.dPadUp then
							up_application.launch()
						end
						if (buttons & xinput.dPadDown) == xinput.dPadDown then
							down_application.launch()
						end
						if (buttons & xinput.dPadLeft) == xinput.dPadLeft then
							left_application.launch()
						end
						if (buttons & xinput.dPadRight) == xinput.dPadRight then
							right_application.launch()
						end
					end
				else
					is_launching_application_button_down = false
				end
			end
		end
	end
)
