# API

## GET

```
GET /led
  [
    {
      red: value,
      green: value,
      blue: value,
    },
    ...
  ]
```

where value is an integer in [0, 256), and the index in the array corresponds to the LED

```
GET /led?index=idx
  {
    red: value,
    green: value,
    blue: value,
  }
```

where
* idx is the index of the led
* value is an integer in [0, 256)

```
GET /led?index=idx&color=color
  value
```

where
* idx is the index of the led
* color is "red", "green", or "blue"
* value is an integer in [0, 256)

```
GET /mode
  mode
```

where
* mode is "IDLE", "UNIFORM_RANDOM", or "EACH_RANDOM"

## POST

```
POST /led
  [
    {
      red: value,
      green: value,
      blue: value,
    },
    ...
  ]
```

where
* value is an integer in [0, 256)
* the index in the array corresponds to the LED
* any and all of the colors are optional

```
POST /led
  {
    index: value,
    red: value,
    green: value,
    blue: value,
  }
```

where
* idx is the index of the led or "all"
* value is an integer in [0, 256)
* any and all of the colors are optional

```
POST /mode
  mode
```

where
* mode is "IDLE", "UNIFORM_RANDOM", or "EACH_RANDOM"
