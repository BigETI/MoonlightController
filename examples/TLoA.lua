-- Virtual keys
local virtual_keys = {
	q = 81,
	w = 87,
	a = 65,
	s = 83,
	d = 68,
	f = 70,
	numpad4 = 100,
	numpad2 = 98,
	enter = 13,
	isDown = false
}

-- Initialize event
events.registerEvent(
	'init',
	function()
		print('========================')
		print('=                      =')
		print('=  TLoA input script   =')
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
		for controller_index=1, xinput.maximalControllerCount do
			if xinput.isConnected(controller_index) then
				local buttons = xinput.getPressedButtons(controller_index)
				if virtual_keys.isDown == false then
					if (buttons & xinput.start) == xinput.start then
						keyboard.clickKey(1, virtual_keys.q)
						keyboard.clickKey(1, virtual_keys.enter)
						virtual_keys.isDown = true
						runtime.exit()
					end
					if (buttons & xinput.dPadUp) == xinput.dPadUp then
						keyboard.clickKey(1, virtual_keys.w)
						keyboard.clickKey(1, virtual_keys.enter)
						virtual_keys.isDown = true
					end
					if (buttons & xinput.dPadDown) == xinput.dPadDown then
						keyboard.clickKey(1, virtual_keys.s)
						keyboard.clickKey(1, virtual_keys.enter)
						virtual_keys.isDown = true
					end
					if (buttons & xinput.dPadLeft) == xinput.dPadLeft then
						keyboard.clickKey(1, virtual_keys.a)
						keyboard.clickKey(1, virtual_keys.enter)
						virtual_keys.isDown = true
					end
					if (buttons & xinput.dPadRight) == xinput.dPadRight then
						keyboard.clickKey(1, virtual_keys.d)
						keyboard.clickKey(1, virtual_keys.enter)
						virtual_keys.isDown = true
					end
					if (buttons & xinput.a) == xinput.a then
						keyboard.clickKey(1, virtual_keys.f)
						keyboard.clickKey(1, virtual_keys.enter)
						virtual_keys.isDown = true
					end
					if (buttons & xinput.back) == xinput.back then
						keyboard.clickKey(1, virtual_keys.numpad4)
						keyboard.clickKey(1, virtual_keys.numpad2)
						keyboard.clickKey(1, virtual_keys.enter)
						virtual_keys.isDown = true
					end
				else
					if (buttons & (xinput.start | xinput.dPadUp | xinput.dPadDown | xinput.dPadLeft | xinput.dPadRight | xinput.a | xinput.back)) == 0 then
						virtual_keys.isDown = false
					end
				end
			end
		end
	end
)
