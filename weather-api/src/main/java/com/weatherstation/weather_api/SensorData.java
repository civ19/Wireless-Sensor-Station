package com.weatherstation.weather_api;

import lombok.Getter;
import lombok.Setter;

@Getter
@Setter
public class SensorData { // making sure
    private double temp;
    private int light;
    private double distance;
}