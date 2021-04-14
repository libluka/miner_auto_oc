# miner_auto_oc
A win32 cli tool to set clock profiles on launch and exit of a miner. This tool strictly uses MSI Afterburner to apply profiles.

## Setup
This tool is intented to be launched through a shortcut or some sort of scripting file.

Before using any of the methods mentioned, you first need to get your cli command ready.

1. Open an elevated command-prompt shell and execute the file with the -h flag.
2. Satisfy each flag argument with the description.
3. Copy the whole command once ensuring it works as intended (do not include the miner_auto_oc prefix).


### Shortcut
1. Place the executable in the directory of your miner.
2. Right-click the file and select 'Create shortcut'. This shortcut may be placed anywhere in your filesystem or kept in the miner directory.

![](https://github.com/libluka/miner_auto_oc/blob/master/images/create_shortcut.png?raw=true)

3. Right-click on the shortcut and find the field named 'Target:'. In that field you will find a path to the executable. Place quotation marks before and after the entire path if there aren't any there already.

![](https://github.com/libluka/miner_auto_oc/blob/master/images/quotation_marks_1.png?raw=true)

4. Paste your previous command after the path with a space between them.

![](https://github.com/libluka/miner_auto_oc/blob/master/images/arguments.png?raw=true)


## Demo

Notepad is being used here in place of the miner as example. Upon opening the shortcut, miner_auto_oc opens as well as the 'miner'. You can see that the profile is set to profile 5 on afterburner.
Upon closing the 'miner', profile 1 is applied and miner_auto_oc monitoring the 'miner' process also closes.

![](https://github.com/libluka/miner_auto_oc/blob/master/images/demonstration.gif?raw=true)
