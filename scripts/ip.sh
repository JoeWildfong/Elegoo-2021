ip=$(ping -c 1 joebot.local | grep -m1 -ohE "[0-9]{3}.[0-9]{3}.[0-9].[0-9]{3}")
sed -i -r "s/\"port\": \".*?\"/\"port\": \"${ip}\"/" ./.vscode/arduino.json