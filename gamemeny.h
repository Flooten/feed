/*
 * FILNAMN:       gamemeny.h
 * PROJEKT:       F.E.E.D.
 * PROGRAMMERARE: joel
 * DATUM:         2012-11-16
 *
 * BESKRIVNING: anger positioner för gamemeny
 *
 *

meny ska ligga på postition: X: 0-1024 Y: 475-576

playerface: X: 25-75 Y: 500-550

healthbar: text "health" på X: 100     Y: 500
           själva baren på  X: 100-200 Y: 525-550

armorbar: text "armor" på X: 200     Y: 500
          själva baren på X: 200-300 Y: 525-550

just nu valda vapet: X: 350-400 Y: 500-550

clip: X: 425-475 Y: 500-525
ammo: X: 500-550 Y: 525-550

inventory på X: 600-1000 Y: 500-550

        envobject_list_.push_back(new EnvironmentObject(glm::vec2(164, 164),
                                                        glm::vec2(64, 64),
                                                        glm::vec2(0.0f, 0.0f),
                                                        Resources::instance()["se"]));

        envobject_list_.push_back(new EnvironmentObject(glm::vec2(100, 164),
                                                        glm::vec2(64, 64),
                                                        glm::vec2(0, 0),
                                                        Resources::instance()["sw"]));

        envobject_list_.push_back(new EnvironmentObject(glm::vec2(164, 100),
                                                        glm::vec2(64, 64),
                                                        glm::vec2(0, 0),
                                                        Resources::instance()["ne"]));

        envobject_list_.push_back(new EnvironmentObject(glm::vec2(100, 100),
                                                        glm::vec2(64, 64),
                                                        glm::vec2(0, 0),
                                                        Resources::instance()["nw"]));*/
