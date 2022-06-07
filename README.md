# Introduction

**Shocker** is a C++ 11 project made for Linux that allows you to configure
the [DualShock 4](https://www.playstation.com/pt-br/accessories/dualshock-4-wireless-controller/)  buttons/triggers/axis
as:

- Keyboard Inputs
- Mouse Input
- Macros
- Commands e.g. `firefox https://github.com/raphaelabrantes/Shocker`

This types of inputs are called actions It probably works for other controllers but I haven't tested.

## Why?

If you are as lazy as I am you know there is a good motive. I wanted to be able to:

1. Use the PS4 controller for games that don't have native support ( not perfect but it works ).
2. Have a easier way to control stream services from afar without a janky setup.
3. Automation of boring tasks.

## Obtaining Shocker sources

```bash
$ git clone https://github.com/raphaelabrantes/Shocker 
```

or alternatively

```bash 
$ git clone git@github.com:raphaelabrantes/Shocker.git
```

## Building Shocker

First time you will need to execute in the project root:

```bash
$ cmake .
```

After that to build just run the command:

```bash
$ cmake --build .
```

## Running
First you need to install
```bash
$  sudo cmake --install .
```
To run simple execute the command

```bash
$ NewShocker 
```

The default profile is in this
path [`$HOME/.shocker/profiles/default.json`](https://github.com/raphaelabrantes/Shocker/blob/master/profiles/text.json), if you want to
run with another profile just run

```bash
$ NewShocker <path/to/new/profile/file>
```

You can and should modify the default profile as what you wish.

# Profiles configuration

Profiles are written in json files following this example.

```json
{
  "R2": {
    "type": "button",
    "value": "ENTER"
  },
  "R3_MU": {
    "type": "mouse",
    "value": "MOUSE_Y",
    "sensibility": 50,
    "positive": false
  },
  "L1": {
    "type": "macro",
    "value": [
      {
        "type": "button",
        "value": "H"
      },
      {
        "type": "button",
        "value": "E"
      },
      {
        "type": "button",
        "value": "L"
      },
      {
        "type": "button",
        "value": "L"
      },
      {
        "type": "button",
        "value": "O"
      }
    ]
  }
}
```

There is 4 types of actions as talked before.

They all follow the same basic layout.

```json
{
  "CONTROLLER_BUTTON": {
    "type": type,
    "value": value
  }
}
```

**Keyboard Input**:

```json
{
  "CONTROLLER_BUTTON": {
    "type": "button",
    "value": "KEYBOARD_OR_MOUSE_BUTTON"
  }
}
 ```

`CONTROLLER_BUTTON` being the name of the key in the DualShock button that you want to bind with,
and `KEYBOARD_OR_MOUSE_BUTTON` being the name of the keyboard or mouse button you want to press

**Mouse Movement Input** :
For now only work with the directionals (up, right, left, down), triggers and axis of the controller.

```json
{
  "CONTROLLER_BUTTON": {
    "type": "mouse",
    "value": "MOUSE_X"
    or
    "MOUSE_Y",
    "positive": <bollean>,
    "sensibility": <int>
  }
}
```

`CONTROLLER_BUTTON` being the name of the key in the DualShock button that you want to bind with.  
In the `mouse` value you can only put or `MOUSE_X` or `MOUSE_Y`, they are the axis of the mouse movement.  
If the `positive` value is true that will move the mouse in the positive direction of the axis (up if `MOUSE_Y` or right
if `MOUSE_X`), if false will move in the negative direction of the axis.  
Sensibility is the max amount of pixels that the axis will move in one iteration (20 ms)  while the button is being
held.

**Macros**

```json
{
  "CONTROLLER_BUTTON": {
    "type": "macro",
    "value": [
      {
        "type": type_of_action,
        "value": value_of_action
      },
      {
        "type": type_of_action,
        "value": value_of_action
      }
    ]
  }
}
 ```

`CONTROLLER_BUTTON` being the name of the key in the DualShock button that you want to bind with.  
The value is an array of actions, can be any type of action, even macros.

**Commands**
It will run any command you can execute in your terminal.

```json
{
  "CONTROLLER_BUTTON": {
    "type": "command",
    "value": "COMMAND"
  }
}
 ```

`CONTROLLER_BUTTON` being the name of the key in the DualShock button that you want to bind with.  
`COMMAND` being the command you want to execute (It will open a non-blocking thread to execute, but It wont be able to
execute again until the command exit, for safety reasons).

**All keyboard and mouse button names can be found in
the [`key_codes/keys.json`](https://github.com/raphaelabrantes/Shocker/blob/master/key_codes/keys.json) file.  ( Except
the MOUSE_X and MOUSE_Y, it wont break but it wont move the mouse )**

All controller buttons names can be found in here or in
the [`profiles/text.json`](https://github.com/raphaelabrantes/Shocker/blob/master/profiles/text.json) :

- SQUARE
- TRIANGLE
- CIRCLE
- X
- L1
- L3
- R1
- R3
- OPT
- SHARE
- L2
- R2
- R3_MU ¹
- R3_MR ²
- R3_ML ³
- R3_MD ⁴
- L3_MU ¹
- L3_MR ²
- L3_ML ³
- L3_MD ⁴
- LEFT_BU ¹
- LEFT_BR ²
- LEFT_BL ³
- LEFT_BD ⁴
- PS

¹ UP

² RIGHT

³ LEFT

⁴ DOWN
