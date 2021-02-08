import requests
import json


ip = '192.168.1.35'

def get_led(index = None):
  if index is None:
    return requests.get(f'http://{ip}/api/led')
  else:
    return requests.get(f'http://{ip}/api/led?index={index}')

def get_mode():
  return requests.get(f'http://{ip}/api/mode')

def post_led(data):
  """
    Example:
    data = [
      {
        'index': 0,
        'red': 255,
        'green': 0,
        'blue': 23,
        'fade_duration': 1000,
        'delay_duration': 0,
      },
      {
        'index': 10,
        'red': 255,
        'green': 0,
        'blue': 23,
        'fade_duration': 1000,
        'delay_duration': 0,
      }
    ]
  """
  requests.post(f'http://{ip}/api/led', data=data)

def post_leds(data):
  """
    Example:
    data = {'red': 255, 'green': 0, 'blue': 23, 'fade_duration': 1000, 'delay_duration': 0, }
  """
  requests.post(f'http://{ip}/api/leds', data=data)

def post_mode(data):
  """
    Example:
    data = {'name': "EACH_RANDOM", 'fade_duration': 1000, 'delay_duration': 1000, }
  """
  requests.post(f'http://{ip}/api/mode', data=data)

def post_brightness(data):
  """
    Example:
    data = {'brightness': 255}
  """
  requests.post(f'http://{ip}/api/brightness', data=data)