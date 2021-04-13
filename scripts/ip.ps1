$count = 0;
$ip = ""
ping -n 1 joebot.local | Select-String -Pattern "[0-9]{3}\.[0-9]{3}\.[0-9]\.[0-9]{3}" | % {if (!$count) {$ip = $_.Matches.Value} $count += 1}
((Get-Content -path .\.vscode\arduino.json -Raw) -replace "`"port`": `"[0-9.]*`"", "`"port`": `"$ip`"") | Set-Content -NoNewline -Path .\.vscode\arduino.json