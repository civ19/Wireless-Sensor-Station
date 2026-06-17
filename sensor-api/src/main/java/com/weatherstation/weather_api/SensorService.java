package com.weatherstation.weather_api;

import lombok.RequiredArgsConstructor;
import org.springframework.stereotype.Service;
import org.springframework.web.reactive.function.client.WebClient;

@Service

@RequiredArgsConstructor
public class SensorService { // <--- MAKE SURE 'public' IS EXPLICITLY WRITTEN HERE
    //webclient startup

    private final WebClient webClient;

    public SensorService() {
        this.webClient = WebClient.builder().baseUrl("http://192.168.0.67").build(); //build a webclient on this IP
    }

    public SensorData fetchData() {
        return webClient.get().uri("/data")
                .retrieve()
                .bodyToMono(SensorData.class) //sensordata as a body
                .block();
    }

}