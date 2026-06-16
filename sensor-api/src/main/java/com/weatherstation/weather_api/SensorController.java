package com.weatherstation.weather_api;

import lombok.RequiredArgsConstructor;
import org.springframework.web.bind.annotation.GetMapping;
import org.springframework.web.bind.annotation.RestController;

@RequiredArgsConstructor
@RestController
public class SensorController {

    private final SensorService service;

    @GetMapping("/weather")
    public SensorData getWeather() {
        return service.fetchData();
    }
}