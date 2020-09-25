package lk.garbage.controller;

import lk.garbage.dto.PlaceDTO;
import lk.garbage.service.PlaceService;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.web.bind.annotation.*;

import java.util.List;

@CrossOrigin
@RestController
@RequestMapping(value = "api/place")
public class PlaceController {

    @Autowired
    private PlaceService placeService;

    @GetMapping(value = "/getPlaces")
    public List<PlaceDTO> getPlaces() {
        return placeService.getPlaces();
    }

}