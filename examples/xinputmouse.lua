-- Mouse speed
local mouseSpeed = 10

-- Scroll speed
local scrollSpeed = 10

-- Is app button down
local isAppButtonDown = false

-- Available applications
local apps = {}
apps[xinput.dPadUp] = 'start osk.exe'
apps[xinput.dPadDown] = 'explorer.exe'
apps[xinput.dPadLeft] = '\"C:\\Program Files\\Mozilla Firefox\\firefox.exe\"'
apps[xinput.dPadRight] = '\"C:\\Program Files (x86)\\Google\\Chrome\\Application\\chrome.exe\"'

-- Start application
function StartApp(appName)
	if type(appName) == 'string' then
		os.execute(appName)
	end
end

-- Init event
event.register('init', function()
	print('init')
end)

-- Tick Event
event.register('tick', function()
	--print('tick')
	local exit_combination = xinput.start | xinput.back | xinput.leftShoulder | xinput.rightShoulder
	for i=1, 4 do
		if xinput.isConnected(i) then
			local buttons = xinput.getButtons(i)
			if (buttons & exit_combination) == exit_combination then
				runtime.exit()
			end
			local x = xinput.getAxis(i, xinput.thumbLX)
			local y = xinput.getAxis(i, xinput.thumbLY)
			local s = xinput.getAxis(i, xinput.thumbRY)
			if x > 1.0 then
				x = 1.0
			elseif x < -1.0 then
				x = -1.0
			end
			if y > 1.0 then
				y = 1.0
			elseif y < -1.0 then
				y = -1.0
			end
			if s > 1.0 then
				s = 1.0
			elseif s < -1.0 then
				s = -1.0
			end
			if (math.abs(x) > 0.0625) or (math.abs(y) > 0.0625) then
				mouse.move(math.floor(x * mouseSpeed), -math.floor(y * mouseSpeed))
			end
			if math.abs(s) > 0.0625 then
				mouse.scroll(math.floor(s * scrollSpeed))
			end
			if (buttons & (xinput.leftThumb | xinput.a | xinput.b)) > 0 then
				mouse.press(mouse.left, true)
			else
				mouse.press(mouse.left, false)
			end
			if (buttons & (xinput.rightThumb | xinput.x | xinput.y)) > 0 then
				mouse.press(mouse.right, true)
			else
				mouse.press(mouse.right, false)
			end
			if (buttons & (xinput.dPadUp | xinput.dPadDown | xinput.dPadLeft | xinput.dPadRight)) > 0 then
				if not isAppButtonDown then
					isAppButtonDown = true
					if (buttons & xinput.dPadUp) == xinput.dPadUp then
						StartApp(apps[xinput.dPadUp])
					end
					if (buttons & xinput.dPadDown) == xinput.dPadDown then
						StartApp(apps[xinput.dPadDown])
					end
					if (buttons & xinput.dPadLeft) == xinput.dPadLeft then
						StartApp(apps[xinput.dPadLeft])
					end
					if (buttons & xinput.dPadRight) == xinput.dPadRight then
						StartApp(apps[xinput.dPadRight])
					end
				end
			else
				isAppButtonDown = false
			end
		end
	end
end)

-- Exit event
event.register('exit', function()
	print('exit')
end)