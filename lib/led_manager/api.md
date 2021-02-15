# API

Note:
* All api calls are prefixed with `/api`
* Any errors will return with a status code of 400 and a json response with
  error as the key and message with the details.

## Modes

### Idle:

```
{
  name: "IDLE",
}
```

### Random

```
{
  name: "RANDOM",
  type: type,
  delay_duration: delay_duration,
  fade_duration: fade_duration,
}
```

Where
* `type` is "UNIFORM" or "INDIVIDUAL"
* `delay_duration` is the duration in ms to pause on the selected random color
* `fade_duration` is the duration in ms to transition to the selected random color

Note
* In uniform mode, all lights change with each other
* In individual mode, each light changes to a random color individually

## GET

### `GET /led`

Returns:
```
[
  {
    index: index,
    red: value,
    green: value,
    blue: value,
  },
  ...
]
```

Where
* `index` is the index of the led
* `value` is the color value as an integer in [0, 256)

Note
* the array will always be sorted by index
* `index` will always correspond to its index in the array

### `GET /led?index=index`

Returns
```
{
  index: index,
  red: value,
  green: value,
  blue: value,
}
```

Where
* `index` is the index of the led
* `value` is the color value as an integer in [0, 256)

### `GET /mode`

Returns
```
{
  name: name
  config_key: config_value,
  ...
}
```

Where
* `name` is "IDLE", "UNIFORM_RANDOM", or "EACH_RANDOM"
* `config_key` and `config_value` are the mode's settings (See Modes section)

### `GET /brightness`

Returns
```
{
  brightness: value,
}
```

## POST

### `POST /led`

Body
```
[
  {
    index: index,
    red: red = undefined,
    green: green = undefined,
    blue: blue = undefined,
    delay_duration: delay_duration = 0,
    fade_duration: fade_duration = 0,
  },
  ...
]
```

Where
* `index` is the index of the led to set
* `red`, `green` and `blue` are integers in [0, 256)
* `delay` is the duration in ms before starting the change and defaults to 0
* `fade` is the duration in ms of the transition time and defaults to 0

Note
* Zero delay and fade means the color is set instantly
* Unspecified colors stay their current value
* Unspecified indexes stay their current value
* Calls while an led is transitioning will overwrite the previous transition

### `POST /leds`

```
  {
    red: value,
    green: value,
    blue: value,
    delay_duration: delay_duration = 0,
    fade_duration: fade_duration = 0,
  }
```

Where
* `value` is an integer in [0, 256)
* `delay_duration` is the duration in ms before starting the change and defaults to 0
* `fade_duration` is the duration in ms of the transition time and defaults to 0

### `POST /mode`

```
{
  mode: name
  config_key: config_value,
  ...
}
```

Where
* `name` is "IDLE", "UNIFORM_RANDOM", or "EACH_RANDOM"
* `config_key` and `config_value` are the mode's settings (See Modes section)

### `POST /brightness`

```
{
  brightness: brightness
  delay_duration: delay_duration = 0,
  fade_duration: fade_duration = 0,
}
```

Where
* `brightness` is an integer from 0 through 255
* `delay_duration` is the duration in ms before starting the change and defaults to 0
* `fade_duration` is the duration in ms of the transition time and defaults to 0

# Future

Random mode with mood config: only warm colors, or cold colors, etc.

Moving colors. Random with staggard delays.

A delay relative to index option for setting

A bounce mode where colors step closer to their neighbor's colors (front and
back are neighbors, optionally)

Optional colors for the /leds api
