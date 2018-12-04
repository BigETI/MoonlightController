-- Virtual keys
local virtualKeys = {}
virtualKeys.q = 81
virtualKeys.w = 87
virtualKeys.a = 65
virtualKeys.s = 83
virtualKeys.d = 68
virtualKeys.f = 70
virtualKeys.numpad4 = 100
virtualKeys.numpad2 = 98
virtualKeys.enter = 13
virtualKeys.isDown = false

-- Init event
event.register('init', function()
	print('=====================')
	print('= TLoA input script =')
	print('= Made by BigETI    =')
	print('=====================')
end)

-- Tick event
event.register('tick', function ()
	for i=1, 4 do
		if xinput.isConnected(i) then
			local buttons = xinput.getButtons(i)
			if virtualKeys.isDown == false then
				if (buttons & xinput.start) == xinput.start then
					keyboard.click(virtualKeys.q)
					keyboard.click(virtualKeys.enter)
					virtualKeys.isDown = true
					runtime.exit()
				end
				if (buttons & xinput.dPadUp) == xinput.dPadUp then
					keyboard.click(virtualKeys.w)
					keyboard.click(virtualKeys.enter)
					virtualKeys.isDown = true
				end
				if (buttons & xinput.dPadDown) == xinput.dPadDown then
					keyboard.click(virtualKeys.s)
					keyboard.click(virtualKeys.enter)
					virtualKeys.isDown = true
				end
				if (buttons & xinput.dPadLeft) == xinput.dPadLeft then
					keyboard.click(virtualKeys.a)
					keyboard.click(virtualKeys.enter)
					virtualKeys.isDown = true
				end
				if (buttons & xinput.dPadRight) == xinput.dPadRight then
					keyboard.click(virtualKeys.d)
					keyboard.click(virtualKeys.enter)
					virtualKeys.isDown = true
				end
				if (buttons & xinput.a) == xinput.a then
					keyboard.click(virtualKeys.f)
					keyboard.click(virtualKeys.enter)
					virtualKeys.isDown = true
				end
				if (buttons & xinput.back) == xinput.back then
					keyboard.click(virtualKeys.numpad4)
					keyboard.click(virtualKeys.numpad2)
					keyboard.click(virtualKeys.enter)
					virtualKeys.isDown = true
				end
			else
				if (buttons & (xinput.start | xinput.dPadUp | xinput.dPadDown | xinput.dPadLeft | xinput.dPadRight | xinput.a | xinput.back)) == 0 then
					virtualKeys.isDown = false
				end
			end
		end
	end
end)
