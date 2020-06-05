# NewHacks2020

Project: Friendly neighbourhood garbage-robot man - here to take out the trash!

### Highlights
- Supports object recognition in real time through information obtained through the Raspberry Pi camera
- Objects are read and translated with Python, then sent to the Arduino
- Robot moves towards the trash once camera inputs have been translated by the Arduino

#### Notes
- Due to Raspberry Pi limitations, camera activity must not be overloaded or FPS will drop to 0.2~
- Objects recognized are limited due to lack of time to train new models

**Credits:** Edje Electronics for TFLite_webcam.py and Tensorflow.org for the pre-trained object recognition models.
