#include <gtest/gtest.h>

#include <cmath>

#include "Slab.h"
#include "GrassSlab.h"
#include "WorldMap.h"
#include "CitySlabDecorator.h"
#include "WaterSlab.h"
#include "DesertSlab.h"
#include "Object.h"
#include "Camera.h"
#include "Model.h"
#include "Sun.h"
#include "SunView.h"
#include "SunViewBasic.h"
#include "SkyController.h"
#include "WoodlandSlab.h"


/**  TESTING SLABS **/
/**  TESTING GRASS  **/
TEST(testGrassSlab, testConstructor) {
    Slab* slab = new GrassSlab;

    auto map_ref = slab->getLocalSlabMap();

    //  Test ground initialized to grass
    for (unsigned i = 0; i < SLAB_SIZE*SLAB_SIZE; ++i) {
        EXPECT_EQ(game::GRASS, map_ref[i]);
    }

    //  Test that collision map is set to zero
    for (unsigned i = 0; i < SLAB_SIZE; ++i) {
        for (unsigned j = 0; j < SLAB_MAX_HEIGHT; ++j) {
            for (unsigned k = 0; k < SLAB_SIZE; ++k) {
                EXPECT_FALSE(slab->collision(i, j, k));
            }
        }
    }

    //  Check collision map edges
    EXPECT_FALSE(slab->collision(-1, 0, 0));
    EXPECT_FALSE(slab->collision(0, 0, -1));
    EXPECT_FALSE(slab->collision(SLAB_SIZE, 0, 0));
    EXPECT_FALSE(slab->collision(0, 0, SLAB_SIZE));

    EXPECT_TRUE(slab->collision(0, -1, 0));
    EXPECT_TRUE(slab->collision(0, SLAB_MAX_HEIGHT, 0));

    //  Check height
    EXPECT_EQ(2, slab->height());

    delete slab;
}
TEST(testGrassSlab, testAddingElement) {
    Slab* slab = new GrassSlab;

    auto map_ref = slab->getCubeMapRef();


    EXPECT_EQ(ADD_SUCCESS, slab->addElement(game::BRICK, glm::vec3(1.0, 1.0, 1.0)));
    EXPECT_EQ(1, map_ref->size());
    EXPECT_EQ(game::BRICK, map_ref->at(0).type);
    EXPECT_TRUE(slab->collision(1, 1, 1));


    EXPECT_EQ(ADD_SUCCESS, slab->addElement(game::ROAD, glm::vec3(2.3, 4.5, 6.63)));
    EXPECT_EQ(2, map_ref->size());
    EXPECT_EQ(game::ROAD, map_ref->at(1).type);
    EXPECT_TRUE(slab->collision(2, 4, 6));


    EXPECT_EQ(POSITION_NOT_VALID, slab->addElement(game::WATER, glm::vec3(-1.0, 0.0, 0.0)));
    EXPECT_EQ(2, map_ref->size());
    EXPECT_FALSE(slab->collision(-1, 0, 0));

    EXPECT_EQ(POSITION_NOT_VALID, slab->addElement(game::WATER, glm::vec3(SLAB_SIZE, 0.0, 0.0)));
    EXPECT_EQ(POSITION_NOT_VALID, slab->addElement(game::WATER, glm::vec3(0, -1, 0)));
    EXPECT_EQ(POSITION_NOT_VALID, slab->addElement(game::WATER, glm::vec3(0, SLAB_MAX_HEIGHT, 0)));
    EXPECT_EQ(POSITION_NOT_VALID, slab->addElement(game::WATER, glm::vec3(0, 0, -1)));
    EXPECT_EQ(POSITION_NOT_VALID, slab->addElement(game::WATER, glm::vec3(0, 0, SLAB_SIZE)));

    EXPECT_EQ(POSITION_ALREADY_TAKEN, slab->addElement(game::ROAD, glm::vec3(1.0, 1.0, 1.0)));


    delete slab;
}

TEST(testGrassSLab, testAddingELement2) {
    Slab* slab = new GrassSlab;
    glm::vec3 temp(0.0, 0.0, 1.0);

    slab->addElement(game::BRICK, glm::vec3(1.0, 1.0, 1.0));
    slab->addElement(game::ROAD, glm::vec3(1.0, 0.0, 1.0));
    slab->addElement(game::WOOD, glm::vec3(1.0, 0.0, 0.0));
    slab->addElement(game::WOOD, glm::vec3(0.0, 0.0, 1.0));

    delete slab;
}



TEST(testGrassSlab, testCheckPosIsValid) {
    Slab* slab = new GrassSlab;

    EXPECT_TRUE(slab->checkPosIsValid(glm::vec3(0.0, 0.0, 0.0)));
    EXPECT_TRUE(slab->checkPosIsValid(glm::vec3(SLAB_SIZE-1, 0.0, 0.0)));
    EXPECT_TRUE(slab->checkPosIsValid(glm::vec3(0.0, SLAB_MAX_HEIGHT-1, 0.0)));
    EXPECT_TRUE(slab->checkPosIsValid(glm::vec3(0.0, 0.0, SLAB_SIZE-1)));

    EXPECT_FALSE(slab->checkPosIsValid(glm::vec3(-1.0, 0.0, 0.0)));
    EXPECT_FALSE(slab->checkPosIsValid(glm::vec3(0.0, -1.0, 0.0)));
    EXPECT_FALSE(slab->checkPosIsValid(glm::vec3(0.0, 0.0, -1.0)));
    EXPECT_FALSE(slab->checkPosIsValid(glm::vec3(SLAB_SIZE, 0.0, 0.0)));
    EXPECT_FALSE(slab->checkPosIsValid(glm::vec3(0.0, SLAB_MAX_HEIGHT, 0.0)));
    EXPECT_FALSE(slab->checkPosIsValid(glm::vec3(0.0, 0.0, SLAB_SIZE)));

    delete slab;
}

TEST(testGrassSlab, testRemoveElement) {
    Slab* slab = new GrassSlab;

    EXPECT_EQ(ADD_SUCCESS, slab->addElement(game::BRICK, glm::vec3(2.6, 4.3, 1.7)));
    EXPECT_EQ(ADD_SUCCESS, slab->addElement(game::GRASS, glm::vec3(1.0, 2.9, 5.3)));

    EXPECT_EQ(REMOVE_SUCCESS, slab->removeElement(glm::vec3(2.0, 4.0, 1.0)));

    EXPECT_EQ(POSITION_NOT_VALID, slab->removeElement(glm::vec3(-1.0, 3.0, 3.0)));

    EXPECT_EQ(POSITION_EMPTY, slab->removeElement(glm::vec3(0.0, 0.0, 0.0)));
    EXPECT_EQ(POSITION_EMPTY, slab->removeElement(glm::vec3(2.0, 4.0, 1.0)));

    delete slab;
}

/**  TESTING WATER SLAB  **/
TEST(testWaterSlab, testConstructor) {
    Slab* slab = new WaterSlab;

    auto map_ref = slab->getLocalSlabMap();

    //  Test ground initialized to grass
    for (unsigned i = 0; i < SLAB_SIZE*SLAB_SIZE; ++i) {
        EXPECT_EQ(game::WATER, map_ref[i]);
    }

    //  Test that collision map is set to zero
    for (unsigned i = 0; i < SLAB_SIZE; ++i) {
        for (unsigned j = 0; j < SLAB_MAX_HEIGHT; ++j) {
            for (unsigned k = 0; k < SLAB_SIZE; ++k) {
                EXPECT_FALSE(slab->collision(i, j, k));
            }
        }
    }

    //  Check collision map edges
    EXPECT_FALSE(slab->collision(-1, 0, 0));
    EXPECT_FALSE(slab->collision(0, 0, -1));
    EXPECT_FALSE(slab->collision(SLAB_SIZE, 0, 0));
    EXPECT_FALSE(slab->collision(0, 0, SLAB_SIZE));

    EXPECT_TRUE(slab->collision(0, -1, 0));
    EXPECT_TRUE(slab->collision(0, SLAB_MAX_HEIGHT, 0));

    //  Check height
    EXPECT_EQ(1, slab->height());

    delete slab;
}
TEST(testWaterSlab, testAddingElement) {
    Slab* slab = new WaterSlab;

    auto map_ref = slab->getCubeMapRef();


    EXPECT_EQ(ADD_SUCCESS, slab->addElement(game::BRICK, glm::vec3(1.0, 1.0, 1.0)));
    EXPECT_EQ(1, map_ref->size());
    EXPECT_EQ(game::BRICK, map_ref->at(0).type);
    EXPECT_TRUE(slab->collision(1, 1, 1));


    EXPECT_EQ(ADD_SUCCESS, slab->addElement(game::ROAD, glm::vec3(2.3, 4.5, 6.63)));
    EXPECT_EQ(2, map_ref->size());
    EXPECT_EQ(game::ROAD, map_ref->at(1).type);
    EXPECT_TRUE(slab->collision(2, 4, 6));


    EXPECT_EQ(POSITION_NOT_VALID, slab->addElement(game::WATER, glm::vec3(-1.0, 0.0, 0.0)));
    EXPECT_EQ(2, map_ref->size());
    EXPECT_FALSE(slab->collision(-1, 0, 0));

    EXPECT_EQ(POSITION_NOT_VALID, slab->addElement(game::WATER, glm::vec3(SLAB_SIZE, 0.0, 0.0)));
    EXPECT_EQ(POSITION_NOT_VALID, slab->addElement(game::WATER, glm::vec3(0, -1, 0)));
    EXPECT_EQ(POSITION_NOT_VALID, slab->addElement(game::WATER, glm::vec3(0, SLAB_MAX_HEIGHT, 0)));
    EXPECT_EQ(POSITION_NOT_VALID, slab->addElement(game::WATER, glm::vec3(0, 0, -1)));
    EXPECT_EQ(POSITION_NOT_VALID, slab->addElement(game::WATER, glm::vec3(0, 0, SLAB_SIZE)));

    EXPECT_EQ(POSITION_ALREADY_TAKEN, slab->addElement(game::ROAD, glm::vec3(1.0, 1.0, 1.0)));

    delete slab;
}

TEST(testWaterSlab, testCheckPosIsValid) {
    Slab* slab = new WaterSlab;

    EXPECT_TRUE(slab->checkPosIsValid(glm::vec3(0.0, 0.0, 0.0)));
    EXPECT_TRUE(slab->checkPosIsValid(glm::vec3(SLAB_SIZE-1, 0.0, 0.0)));
    EXPECT_TRUE(slab->checkPosIsValid(glm::vec3(0.0, SLAB_MAX_HEIGHT-1, 0.0)));
    EXPECT_TRUE(slab->checkPosIsValid(glm::vec3(0.0, 0.0, SLAB_SIZE-1)));

    EXPECT_FALSE(slab->checkPosIsValid(glm::vec3(-1.0, 0.0, 0.0)));
    EXPECT_FALSE(slab->checkPosIsValid(glm::vec3(0.0, -1.0, 0.0)));
    EXPECT_FALSE(slab->checkPosIsValid(glm::vec3(0.0, 0.0, -1.0)));
    EXPECT_FALSE(slab->checkPosIsValid(glm::vec3(SLAB_SIZE, 0.0, 0.0)));
    EXPECT_FALSE(slab->checkPosIsValid(glm::vec3(0.0, SLAB_MAX_HEIGHT, 0.0)));
    EXPECT_FALSE(slab->checkPosIsValid(glm::vec3(0.0, 0.0, SLAB_SIZE)));

    delete slab;
}

TEST(testWaterSlab, testRemoveElement) {
    Slab* slab = new WaterSlab;

    EXPECT_EQ(ADD_SUCCESS, slab->addElement(game::BRICK, glm::vec3(2.6, 4.3, 1.7)));
    EXPECT_EQ(ADD_SUCCESS, slab->addElement(game::GRASS, glm::vec3(1.0, 2.9, 5.3)));

    EXPECT_EQ(REMOVE_SUCCESS, slab->removeElement(glm::vec3(2.0, 4.0, 1.0)));

    EXPECT_EQ(POSITION_NOT_VALID, slab->removeElement(glm::vec3(-1.0, 3.0, 3.0)));

    EXPECT_EQ(POSITION_EMPTY, slab->removeElement(glm::vec3(0.0, 0.0, 0.0)));
    EXPECT_EQ(POSITION_EMPTY, slab->removeElement(glm::vec3(2.0, 4.0, 1.0)));

    delete slab;
}


/**  TESTING DESERT MAP  **/
TEST(testDesertSlab, testConstructor) {
    Slab* slab = new DesertSlab;

    auto map_ref = slab->getLocalSlabMap();

    //  Test ground initialized to grass
    for (unsigned i = 0; i < SLAB_SIZE*SLAB_SIZE; ++i) {
        EXPECT_EQ(game::DESERT, map_ref[i]);
    }

    //  Test that collision map is set to zero
    for (unsigned i = 0; i < SLAB_SIZE; ++i) {
        for (unsigned j = 0; j < SLAB_MAX_HEIGHT; ++j) {
            for (unsigned k = 0; k < SLAB_SIZE; ++k) {
                EXPECT_FALSE(slab->collision(i, j, k));
            }
        }
    }

    //  Check collision map edges
    EXPECT_FALSE(slab->collision(-1, 0, 0));
    EXPECT_FALSE(slab->collision(0, 0, -1));
    EXPECT_FALSE(slab->collision(SLAB_SIZE, 0, 0));
    EXPECT_FALSE(slab->collision(0, 0, SLAB_SIZE));

    EXPECT_TRUE(slab->collision(0, -1, 0));
    EXPECT_TRUE(slab->collision(0, SLAB_MAX_HEIGHT, 0));

    //  Check height
    EXPECT_EQ(2, slab->height());

    delete slab;
}
TEST(testDesertSlab, testAddingElement) {
    Slab* slab = new DesertSlab;

    auto map_ref = slab->getCubeMapRef();


    EXPECT_EQ(ADD_SUCCESS, slab->addElement(game::BRICK, glm::vec3(1.0, 1.0, 1.0)));
    EXPECT_EQ(1, map_ref->size());
    EXPECT_EQ(game::BRICK, map_ref->at(0).type);
    EXPECT_TRUE(slab->collision(1, 1, 1));


    EXPECT_EQ(ADD_SUCCESS, slab->addElement(game::ROAD, glm::vec3(2.3, 4.5, 6.63)));
    EXPECT_EQ(2, map_ref->size());
    EXPECT_EQ(game::ROAD, map_ref->at(1).type);
    EXPECT_TRUE(slab->collision(2, 4, 6));


    EXPECT_EQ(POSITION_NOT_VALID, slab->addElement(game::WATER, glm::vec3(-1.0, 0.0, 0.0)));
    EXPECT_EQ(2, map_ref->size());
    EXPECT_FALSE(slab->collision(-1, 0, 0));

    EXPECT_EQ(POSITION_NOT_VALID, slab->addElement(game::WATER, glm::vec3(SLAB_SIZE, 0.0, 0.0)));
    EXPECT_EQ(POSITION_NOT_VALID, slab->addElement(game::WATER, glm::vec3(0, -1, 0)));
    EXPECT_EQ(POSITION_NOT_VALID, slab->addElement(game::WATER, glm::vec3(0, SLAB_MAX_HEIGHT, 0)));
    EXPECT_EQ(POSITION_NOT_VALID, slab->addElement(game::WATER, glm::vec3(0, 0, -1)));
    EXPECT_EQ(POSITION_NOT_VALID, slab->addElement(game::WATER, glm::vec3(0, 0, SLAB_SIZE)));

    EXPECT_EQ(POSITION_ALREADY_TAKEN, slab->addElement(game::ROAD, glm::vec3(1.0, 1.0, 1.0)));

    delete slab;
}
TEST(testDesertSlab, testCheckPosIsValid) {
    Slab* slab = new DesertSlab;

    EXPECT_TRUE(slab->checkPosIsValid(glm::vec3(0.0, 0.0, 0.0)));
    EXPECT_TRUE(slab->checkPosIsValid(glm::vec3(SLAB_SIZE-1, 0.0, 0.0)));
    EXPECT_TRUE(slab->checkPosIsValid(glm::vec3(0.0, SLAB_MAX_HEIGHT-1, 0.0)));
    EXPECT_TRUE(slab->checkPosIsValid(glm::vec3(0.0, 0.0, SLAB_SIZE-1)));

    EXPECT_FALSE(slab->checkPosIsValid(glm::vec3(-1.0, 0.0, 0.0)));
    EXPECT_FALSE(slab->checkPosIsValid(glm::vec3(0.0, -1.0, 0.0)));
    EXPECT_FALSE(slab->checkPosIsValid(glm::vec3(0.0, 0.0, -1.0)));
    EXPECT_FALSE(slab->checkPosIsValid(glm::vec3(SLAB_SIZE, 0.0, 0.0)));
    EXPECT_FALSE(slab->checkPosIsValid(glm::vec3(0.0, SLAB_MAX_HEIGHT, 0.0)));
    EXPECT_FALSE(slab->checkPosIsValid(glm::vec3(0.0, 0.0, SLAB_SIZE)));

    delete slab;
}

TEST(testDesertSlab, testRemoveElement) {
    Slab* slab = new DesertSlab;

    EXPECT_EQ(ADD_SUCCESS, slab->addElement(game::BRICK, glm::vec3(2.6, 4.3, 1.7)));
    EXPECT_EQ(ADD_SUCCESS, slab->addElement(game::GRASS, glm::vec3(1.0, 2.9, 5.3)));

    EXPECT_EQ(REMOVE_SUCCESS, slab->removeElement(glm::vec3(2.0, 4.0, 1.0)));

    EXPECT_EQ(POSITION_NOT_VALID, slab->removeElement(glm::vec3(-1.0, 3.0, 3.0)));

    EXPECT_EQ(POSITION_EMPTY, slab->removeElement(glm::vec3(0.0, 0.0, 0.0)));
    EXPECT_EQ(POSITION_EMPTY, slab->removeElement(glm::vec3(2.0, 4.0, 1.0)));

    delete slab;
}

/**  TESTING WOODLAND SLAB **/
TEST(testWoodlandSlab, testConstructor) {
    Slab* slab = new WoodlandSlab;

    auto map_ref = slab->getLocalSlabMap();

    //  Test ground initialized to grass
    for (unsigned i = 0; i < SLAB_SIZE*SLAB_SIZE; ++i) {
        EXPECT_EQ(game::WOODLAND, map_ref[i]);
    }

    //  Test that collision map is set to zero
    for (unsigned i = 0; i < SLAB_SIZE; ++i) {
        for (unsigned j = 0; j < SLAB_MAX_HEIGHT; ++j) {
            for (unsigned k = 0; k < SLAB_SIZE; ++k) {
                EXPECT_FALSE(slab->collision(i, j, k));
            }
        }
    }

    //  Check collision map edges
    EXPECT_FALSE(slab->collision(-1, 0, 0));
    EXPECT_FALSE(slab->collision(0, 0, -1));
    EXPECT_FALSE(slab->collision(SLAB_SIZE, 0, 0));
    EXPECT_FALSE(slab->collision(0, 0, SLAB_SIZE));

    EXPECT_TRUE(slab->collision(0, -1, 0));
    EXPECT_TRUE(slab->collision(0, SLAB_MAX_HEIGHT, 0));

    //  Check height
    EXPECT_EQ(2, slab->height());

    delete slab;
}

/**  TESTING CITY WRAPPER  **/
TEST(testCitySlabDecorator, testConstructor) {
    Slab* slab = new CitySlabDecorator(new GrassSlab);

    auto map_ref = slab->getLocalSlabMap();

    //  Test for road tiles
    EXPECT_EQ(game::ROAD, map_ref[0]);

    //  Test that collision map is set to zero
    for (unsigned i = 0; i < SLAB_SIZE; ++i) {
        for (unsigned j = 0; j < SLAB_MAX_HEIGHT; ++j) {
            for (unsigned k = 0; k < SLAB_SIZE; ++k) {
                EXPECT_FALSE(slab->collision(i, j, k));
            }
        }
    }

    //  Check collision map edges
    EXPECT_FALSE(slab->collision(-1, 0, 0));
    EXPECT_FALSE(slab->collision(0, 0, -1));
    EXPECT_FALSE(slab->collision(SLAB_SIZE, 0, 0));
    EXPECT_FALSE(slab->collision(0, 0, SLAB_SIZE));

    EXPECT_TRUE(slab->collision(0, -1, 0));
    EXPECT_TRUE(slab->collision(0, SLAB_MAX_HEIGHT, 0));

    //  Check height
    EXPECT_EQ(2, slab->height());

    delete slab;
}
TEST(testCitySlabDecorator, testAddingElement) {
    Slab* slab = new CitySlabDecorator(new WaterSlab);

    auto map_ref = slab->getCubeMapRef();


    EXPECT_EQ(ADD_SUCCESS, slab->addElement(game::BRICK, glm::vec3(1.0, 1.0, 1.0)));
    EXPECT_EQ(1, map_ref->size());
    EXPECT_EQ(game::BRICK, map_ref->at(0).type);
    EXPECT_TRUE(slab->collision(1, 1, 1));


    EXPECT_EQ(ADD_SUCCESS, slab->addElement(game::ROAD, glm::vec3(2.3, 4.5, 6.63)));
    EXPECT_EQ(2, map_ref->size());
    EXPECT_EQ(game::ROAD, map_ref->at(1).type);
    EXPECT_TRUE(slab->collision(2, 4, 6));


    EXPECT_EQ(POSITION_NOT_VALID, slab->addElement(game::WATER, glm::vec3(-1.0, 0.0, 0.0)));
    EXPECT_EQ(2, map_ref->size());
    EXPECT_FALSE(slab->collision(-1, 0, 0));

    EXPECT_EQ(POSITION_NOT_VALID, slab->addElement(game::WATER, glm::vec3(SLAB_SIZE, 0.0, 0.0)));
    EXPECT_EQ(POSITION_NOT_VALID, slab->addElement(game::WATER, glm::vec3(0, -1, 0)));
    EXPECT_EQ(POSITION_NOT_VALID, slab->addElement(game::WATER, glm::vec3(0, SLAB_MAX_HEIGHT, 0)));
    EXPECT_EQ(POSITION_NOT_VALID, slab->addElement(game::WATER, glm::vec3(0, 0, -1)));
    EXPECT_EQ(POSITION_NOT_VALID, slab->addElement(game::WATER, glm::vec3(0, 0, SLAB_SIZE)));

    EXPECT_EQ(POSITION_ALREADY_TAKEN, slab->addElement(game::ROAD, glm::vec3(1.0, 1.0, 1.0)));


    delete slab;
}
TEST(testCitySlabDecorator, testCheckPosIsValid) {
    Slab* slab = new CitySlabDecorator(new DesertSlab);

    EXPECT_TRUE(slab->checkPosIsValid(glm::vec3(0.0, 0.0, 0.0)));
    EXPECT_TRUE(slab->checkPosIsValid(glm::vec3(SLAB_SIZE-1, 0.0, 0.0)));
    EXPECT_TRUE(slab->checkPosIsValid(glm::vec3(0.0, SLAB_MAX_HEIGHT-1, 0.0)));
    EXPECT_TRUE(slab->checkPosIsValid(glm::vec3(0.0, 0.0, SLAB_SIZE-1)));

    EXPECT_FALSE(slab->checkPosIsValid(glm::vec3(-1.0, 0.0, 0.0)));
    EXPECT_FALSE(slab->checkPosIsValid(glm::vec3(0.0, -1.0, 0.0)));
    EXPECT_FALSE(slab->checkPosIsValid(glm::vec3(0.0, 0.0, -1.0)));
    EXPECT_FALSE(slab->checkPosIsValid(glm::vec3(SLAB_SIZE, 0.0, 0.0)));
    EXPECT_FALSE(slab->checkPosIsValid(glm::vec3(0.0, SLAB_MAX_HEIGHT, 0.0)));
    EXPECT_FALSE(slab->checkPosIsValid(glm::vec3(0.0, 0.0, SLAB_SIZE)));

    delete slab;
}

TEST(testCitySlab, testRemoveElement) {
    Slab* slab = new CitySlabDecorator(new DesertSlab);

    EXPECT_EQ(ADD_SUCCESS, slab->addElement(game::BRICK, glm::vec3(2.6, 4.3, 1.7)));
    EXPECT_EQ(ADD_SUCCESS, slab->addElement(game::GRASS, glm::vec3(1.0, 2.9, 5.3)));

    EXPECT_EQ(REMOVE_SUCCESS, slab->removeElement(glm::vec3(2.0, 4.0, 1.0)));

    EXPECT_EQ(POSITION_NOT_VALID, slab->removeElement(glm::vec3(-1.0, 3.0, 3.0)));

    EXPECT_EQ(POSITION_EMPTY, slab->removeElement(glm::vec3(0.0, 0.0, 0.0)));
    EXPECT_EQ(POSITION_EMPTY, slab->removeElement(glm::vec3(2.0, 4.0, 1.0)));

    delete slab;
}


/**  TESTING WORLD MAP  **/
TEST(testWorldMap, testConstructor) {
    WorldMap game_map(5);
    auto map_copy = game_map.getWorldMap();
    EXPECT_EQ(25, map_copy->capacity());
    EXPECT_EQ(0, map_copy->size());
}

//  Adding too little slabs
TEST(testWorldMap, testAddSlab) {
    WorldMap* game_map = new WorldMap(3);
    auto map_ref = game_map->getWorldMap();

    game_map->addSlab(new GrassSlab);
    game_map->addSlab(new GrassSlab);

    EXPECT_EQ(2, map_ref->size());

    delete game_map;
}

//  Adding too many slabs
TEST(testWorldMap, testAddSlab2) {
    WorldMap game_map(2);
    auto map_ref = game_map.getWorldMap();

    for (int i = 0; i < 5; ++i) {
        game_map.addSlab(new GrassSlab);
    }
    EXPECT_EQ(4, map_ref->size());
}

//  Adding just enough slabs
TEST(testWorldMap, testAddSlab3) {
    WorldMap game_map(15);
    auto map_ref = game_map.getWorldMap();

    for (int i = 0; i < 15*15; ++i){
        game_map.addSlab(new GrassSlab);
    }

    EXPECT_EQ(15*15, map_ref->size());
}


TEST(testWorldMap, testFillRestOfMap) {
    WorldMap* game_map = new WorldMap(3);
    auto map_ref = game_map->getWorldMap();

    EXPECT_EQ(0, map_ref->size());

    game_map->fillRestOfMap();
    EXPECT_EQ(9, map_ref->size());

    delete game_map;
}

TEST(testWorldMap, testGetSlabIndex) {
    WorldMap game_map(4);

    game_map.fillRestOfMap();

    EXPECT_EQ(-1, game_map.getSlabIndex(-1, 0));
    EXPECT_EQ(-1, game_map.getSlabIndex(0, -1));

    EXPECT_EQ(-1, game_map.getSlabIndex(4, 0));
    EXPECT_EQ(-1, game_map.getSlabIndex(0, 4));

    EXPECT_EQ(0, game_map.getSlabIndex(0, 0));
    EXPECT_EQ(1, game_map.getSlabIndex(0, 1));
    EXPECT_EQ(2, game_map.getSlabIndex(0, 2));
    EXPECT_EQ(3, game_map.getSlabIndex(0, 3));
    EXPECT_EQ(4, game_map.getSlabIndex(1, 0));
    EXPECT_EQ(5, game_map.getSlabIndex(1, 1));
    EXPECT_EQ(6, game_map.getSlabIndex(1, 2));
    EXPECT_EQ(7, game_map.getSlabIndex(1, 3));
    EXPECT_EQ(8, game_map.getSlabIndex(2, 0));
    EXPECT_EQ(9, game_map.getSlabIndex(2, 1));
    EXPECT_EQ(10, game_map.getSlabIndex(2, 2));
    EXPECT_EQ(11, game_map.getSlabIndex(2, 3));
    EXPECT_EQ(12, game_map.getSlabIndex(3, 0));
    EXPECT_EQ(13, game_map.getSlabIndex(3, 1));
    EXPECT_EQ(14, game_map.getSlabIndex(3, 2));
    EXPECT_EQ(15, game_map.getSlabIndex(3, 3));
}

TEST(testWorldMap, testMapIsSquare) {
    WorldMap game_map(3);

    EXPECT_TRUE(game_map.mapIsSquare());
    int i = 0;
    for (; i < 3; ++i) {
        game_map.addSlab(new GrassSlab);
    }
    EXPECT_FALSE(game_map.mapIsSquare());

    ++i;
    game_map.addSlab(new GrassSlab);
    EXPECT_TRUE(game_map.mapIsSquare());

    for (; i < 8; ++i) {
        game_map.addSlab(new GrassSlab);
    }
    EXPECT_FALSE(game_map.mapIsSquare());

    game_map.addSlab(new GrassSlab);
    EXPECT_TRUE(game_map.mapIsSquare());

}

TEST(testWorldMap, testMapIsFull) {
    WorldMap game_map(3);
    EXPECT_FALSE(game_map.mapIsFull());
    for (int i = 0; i < 8; ++i) {
        game_map.addSlab(new GrassSlab);
    }
    EXPECT_FALSE(game_map.mapIsFull());
    game_map.addSlab(new GrassSlab);
    EXPECT_TRUE(game_map.mapIsFull());
}

TEST(testWorldMap, testFillingMapWithDifferentSlabs) {
    //  Game Map
    WorldMap game_map(3);
    game_map.addSlab(new CitySlabDecorator(new GrassSlab));
    game_map.addSlab(new CitySlabDecorator(new DesertSlab));
    game_map.addSlab(new CitySlabDecorator(new GrassSlab));
    game_map.addSlab(new GrassSlab);
    game_map.addSlab(new GrassSlab);
    game_map.addSlab(new WaterSlab);
    game_map.addSlab(new GrassSlab);
    game_map.addSlab(new DesertSlab);
    game_map.addSlab(new GrassSlab);
}

TEST(testWorldMap, testCollision) {
    WorldMap game_map(3);

    Slab* slab = new GrassSlab;

    slab->addElement(game::ROCK, glm::vec3(0.0, 1.0, 3.0));

    game_map.addSlab(slab);

    game_map.fillRestOfMap();

    EXPECT_FALSE(game_map.collision(glm::vec3(0.0, 2.5, 0.0)));
    EXPECT_TRUE(game_map.collision(glm::vec3(0.0, 0.0, 0.0)));

    EXPECT_TRUE(game_map.collision(glm::vec3(0.0, 3.0, 3.0)));

    EXPECT_TRUE(game_map.collision(glm::vec3(-1.0, 4.0, 0.0)));
    EXPECT_TRUE(game_map.collision(glm::vec3(0.0, -1.0, 0.0)));
    EXPECT_TRUE(game_map.collision(glm::vec3(0.0, 4.0, -1.0)));
    EXPECT_TRUE(game_map.collision(glm::vec3(3 * SLAB_SIZE, 4.0, 0.0)));
    EXPECT_TRUE(game_map.collision(glm::vec3(0.0, SLAB_MAX_HEIGHT + 2.0, 0.0)));
    EXPECT_TRUE(game_map.collision(glm::vec3(0.0, 4.0, 3 * SLAB_SIZE)));

    EXPECT_FALSE(game_map.collision(glm::vec3(3*SLAB_SIZE -1, 4.0, 0.0)));
    EXPECT_FALSE(game_map.collision(glm::vec3(0.0, 4.0, 3*SLAB_SIZE-1)));
    EXPECT_FALSE(game_map.collision(glm::vec3(0.0, SLAB_MAX_HEIGHT+1.0, 0.0)));
}

TEST(testWorldMap, testCovertToLocalSlabCoordinates) {
    WorldMap game_map(4);

    game_map.fillRestOfMap();

    float local_slab_x, local_slab_z;

    for (unsigned i = 0; i < 4 * SLAB_SIZE; i += SLAB_SIZE) {
        game_map.convertToLocalSlabCoordintates(glm::vec3(i + 3, 0, i + 5),
                                                local_slab_x, local_slab_z);
        EXPECT_TRUE(abs(3 - local_slab_x) < 0.00001);
        EXPECT_TRUE(abs(5 - local_slab_z) < 0.00001);
    }
}

TEST(testWorldMap, test2) {
//  Game Map
    WorldMap* game_map = new WorldMap(7);

    Slab* temp_slab = new GrassSlab;
    temp_slab->addElement(game::ROCK, glm::vec3(0, 1, 0 ));
    temp_slab->addElement(game::ROCK, glm::vec3(SLAB_SIZE/2, 0, SLAB_SIZE/2));
    temp_slab->addElement(game::ROCK, glm::vec3(SLAB_SIZE/2 + 1, 0, SLAB_SIZE/2));
    temp_slab->addElement(game::ROCK, glm::vec3(SLAB_SIZE/2 + 2, 0, SLAB_SIZE/2));
    temp_slab->addElement(game::ROCK, glm::vec3(SLAB_SIZE/2 + 3, 0, SLAB_SIZE/2));
    temp_slab->addElement(game::ROCK, glm::vec3(SLAB_SIZE/2 + 4, 0, SLAB_SIZE/2));
    temp_slab->addElement(game::BRICK, glm::vec3(5, 5, 5));

    Slab* temp_slab2 = new DesertSlab;
    for(int i = 0; i < 6; ++i) {
        for (int k = 0; k < 4; ++k) {
            temp_slab2->addElement(game::BRICK, glm::vec3(i, k, 0));
            temp_slab2->addElement(game::BRICK, glm::vec3(i+6, k, 0));
        }


    }
    temp_slab2->addElement(game::BRICK, glm::vec3(0, 1, 0));


    game_map->addSlab(new GrassSlab);
    game_map->addSlab(temp_slab);
    game_map->addSlab(new GrassSlab);
    game_map->addSlab(new DesertSlab);
    game_map->addSlab(new GrassSlab);
    game_map->addSlab(new GrassSlab);
    game_map->addSlab(new GrassSlab);


    game_map->addSlab(new GrassSlab);
    game_map->addSlab(temp_slab2);
    game_map->addSlab(new CitySlabDecorator(new GrassSlab));
    game_map->addSlab(new GrassSlab);
    game_map->addSlab(new GrassSlab);
    game_map->addSlab(new CitySlabDecorator(new GrassSlab));
    game_map->addSlab(new GrassSlab);


    game_map->addSlab(new GrassSlab);
    game_map->addSlab(new DesertSlab);
    game_map->addSlab(new DesertSlab);
    game_map->addSlab(new WaterSlab);
    game_map->addSlab(new CitySlabDecorator(new DesertSlab));
    game_map->addSlab(new CitySlabDecorator(new DesertSlab));
    game_map->addSlab(new DesertSlab);


    game_map->addSlab(new WaterSlab);
    game_map->addSlab(new DesertSlab);
    game_map->addSlab(new DesertSlab);
    game_map->addSlab(new WaterSlab);
    game_map->addSlab(new CitySlabDecorator(new DesertSlab));
    game_map->addSlab(new CitySlabDecorator(new DesertSlab));
    game_map->addSlab(new DesertSlab);


    game_map->addSlab(new WaterSlab);
    game_map->addSlab(new WaterSlab);
    game_map->addSlab(new WaterSlab);
    game_map->addSlab(new WaterSlab);
    game_map->addSlab(new DesertSlab);
    game_map->addSlab(new DesertSlab);
    game_map->addSlab(new DesertSlab);


    game_map->addSlab(new DesertSlab);
    game_map->addSlab(new DesertSlab);
    game_map->addSlab(new DesertSlab);
    game_map->addSlab(new WaterSlab);
    game_map->addSlab(new WaterSlab);
    game_map->addSlab(new WaterSlab);
    game_map->addSlab(new WaterSlab);


    game_map->addSlab(new GrassSlab);
    game_map->addSlab(new GrassSlab);
    game_map->addSlab(new GrassSlab);
    game_map->addSlab(new DesertSlab);
    game_map->addSlab(new GrassSlab);
    game_map->addSlab(new GrassSlab);
    game_map->addSlab(new GrassSlab);

    game_map->fillRestOfMap();

    delete game_map;
}

TEST(testWorldMap, testGetMousePointerLocation) {
    Camera camera;
    camera.pos = glm::vec3(1.0, 5.0, 1.0);

    camera.pitch = 1.0f;
    camera.yaw = 45.0f;

    WorldMap game_map(1);

    Slab* slab = new GrassSlab;

    slab->addElement(game::GRASS, glm::vec3(2.0, 4.5, 2.0));

    game_map.addSlab(slab);

    auto vec = game_map.getMousePointerLocation(camera, ADD);
    EXPECT_TRUE(vec.x - -1.0 < 0.00001);

}

TEST(testWorldMap, testAddCube) {
    WorldMap game_map(2);

    Slab* slab = new DesertSlab;

    game_map.addSlab(slab);
    game_map.addSlab(new GrassSlab);
    game_map.addSlab(new GrassSlab);
    game_map.addSlab(new GrassSlab);

    EXPECT_TRUE(game_map.addCube(game::BRICK, glm::vec3(0.0, 3.0, 0.0), glm::vec3(1.0, 3.0, 1.0)));

    EXPECT_TRUE(slab->collision(1.0, 1.0, 1.0));
    EXPECT_FALSE(slab->collision(0.0, 0.0, 0.0));
}

TEST(testWorldMap, testRemoveCube) {
    WorldMap game_map(2);

    Slab* slab = new GrassSlab;

    game_map.addSlab(slab);
    game_map.addSlab(new DesertSlab);
    game_map.addSlab(new DesertSlab);
    game_map.addSlab(new DesertSlab);

    EXPECT_TRUE(game_map.addCube(game::ROAD, glm::vec3(1.0, 3.0, 4.0), glm::vec3(1.0, 2.0, 3.0)));

    EXPECT_TRUE(slab->collision(1, 0, 3));

    EXPECT_TRUE(game_map.removeCube(glm::vec3(1.0, 2.0, 3.0)));

    EXPECT_FALSE(slab->collision(1, 0, 3));

}

/**  TEST SUN **/
TEST(testSun, testConstructor) {
    Sun sun(new SunViewBasic, 20.0f);
    EXPECT_EQ(0, sun.theta());
    sun.setTheta(30.0f);
    EXPECT_TRUE(sun.theta() - 30.0f < 0.000001);
    sun.update(10.0f, glm::vec3(5.0, 5.0, 5.0));
    EXPECT_TRUE(sun.theta() - 40.0f < 0.0000001);
}

TEST(testSky, SkyConstructor) {


}

/**  TEST OBJECT  **/
/*
TEST(testObject, testConstructor) {
    Object tree("objects/tree.obj");

    EXPECT_TRUE(tree.init());

}

*/
/** TEST CUBE **/
TEST(testCube, testConstructor) {
    //glfwInit();

    //game::Model m1("objects/tree1/tree1.obj");

    //glfwTerminate();
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}

