package com.weatherstation.weather_api;

import org.springframework.web.bind.annotation.GetMapping;
import org.springframework.web.bind.annotation.RestController;

@RestController
public class WeatherController {

    @GetMapping("/app.js")
    public void handleJS() {

    }
}