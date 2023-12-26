#include "Scene.hpp"
#include "./Materials/simplematerial.hpp"
#include "./Materials/simplerefractive.hpp"
#include "./Textures/checker.hpp"
#include "./Textures/image.hpp"
#include "./Textures/gradient.hpp"
#include "./Textures/basicvalnoise.hpp"
#include "./Textures/basicnoise.hpp"
#include "./Textures/marble.hpp"
#include "./Textures/qbStone1.hpp"

using namespace std;

qbRT::Scene::Scene()
{
	//*************************************
	// Configure the camera.
	//*************************************

	//m_camera.SetPosition(	qbVector<double>{std::vector<double> {4.0, -8.0, -2.0}});
	m_camera.SetPosition(qbVector<double>{std::vector<double> {2.0, -5.0, -1.0}});
	//m_camera.SetPosition( qbVector<double>{std::vector<double> {-3.0, -5.0, -2.0}});
	m_camera.SetLookAt(qbVector<double>{std::vector<double> {-0.5, 0.0, 0.0}});
	m_camera.SetUp(qbVector<double>{std::vector<double> {0.0, 0.0, 1.0}});
	//m_camera.SetHorzSize(0.25);
	//m_camera.SetHorzSize(0.85);
	m_camera.SetHorzSize(1.0);
	//m_camera.SetLength(3.0);
	m_camera.SetAspect(16.0 / 9.0);
	//m_camera.SetAspect(1.0);
	m_camera.UpdateCameraGeometry();

    //*************************************
	// Setup ambient lightling.
	//*************************************

	qbRT::MaterialBase::m_ambientColor = std::vector<double>{1.0, 1.0, 1.0};
	//qbRT::MaterialBase::m_ambientIntensity = 0.2;
	qbRT::MaterialBase::m_ambientIntensity = 0.0;


	//*************************************
	// Create some color maps.
    //*************************************

     auto noiseMap = std::make_shared<qbRT::Texture::ColorMap> (qbRT::Texture::ColorMap());
	noiseMap -> SetStop(0.0, qbVector<double>{std::vector<double>{1.0, 0.4, 0.0, 1.0}});//red
	noiseMap -> SetStop(0.5, qbVector<double>{std::vector<double>{0.2, 0.4, 0.8, 1.0}});//green
	noiseMap -> SetStop(1.0, qbVector<double>{std::vector<double>{1.0, 0.8, 0.0, 1.0}});//blue

	auto noiseMap2 = std::make_shared<qbRT::Texture::ColorMap> (qbRT::Texture::ColorMap());
	noiseMap2 -> SetStop(0.0, qbVector<double>{std::vector<double>{1.0, 0.8, 0.0, 1.0}});//blue
	noiseMap2 -> SetStop(0.5, qbVector<double>{std::vector<double>{1.0, 1.0, 1.0, 0.0}});//white
	noiseMap2 -> SetStop(1.0, qbVector<double>{std::vector<double>{1.0, 0.4, 0.0, 1.0}});//red

	auto noiseMap3 = std::make_shared<qbRT::Texture::ColorMap> (qbRT::Texture::ColorMap());
	noiseMap3 -> SetStop(0.0, qbVector<double>{std::vector<double>{1.0, 1.0, 0.0, 1.0}});
	noiseMap3 -> SetStop(0.5, qbVector<double>{std::vector<double>{1.0, 1.0, 1.0, 0.0}});
	noiseMap3 -> SetStop(1.0, qbVector<double>{std::vector<double>{1.0, 0.0, 1.0, 1.0}});
    
	auto cloudMap = std::make_shared<qbRT::Texture::ColorMap> (qbRT::Texture::ColorMap());
	cloudMap -> SetStop(0.0, qbVector<double>{std::vector<double>{0.2, 0.4, 0.8, 1.0}});
	cloudMap -> SetStop(0.75, qbVector<double>{std::vector<double>{1.0, 1.0, 1.0, 1.0}});
	cloudMap -> SetStop(1.0, qbVector<double>{std::vector<double>{0.7, 0.7, 0.7, 1.0}});
	
	auto marbleMap = std::make_shared<qbRT::Texture::ColorMap> (qbRT::Texture::ColorMap());
	marbleMap -> SetStop(0.0, qbVector<double>{std::vector<double>{1.0, 1.0, 1.0, 1.0}});
	marbleMap -> SetStop(0.2, qbVector<double>{std::vector<double>{1.0, 1.0, 1.0, 1.0}});
	marbleMap -> SetStop(0.5, qbVector<double>{std::vector<double>{1.0, 0.4, 0.0, 1.0}});
	marbleMap -> SetStop(0.8, qbVector<double>{std::vector<double>{1.0, 1.0, 1.0, 1.0}});
	marbleMap -> SetStop(1.0, qbVector<double>{std::vector<double>{1.0, 1.0, 1.0, 1.0}});
	
	auto candyMap = std::make_shared<qbRT::Texture::ColorMap> (qbRT::Texture::ColorMap());
	candyMap -> SetStop(0.0, qbVector<double>{std::vector<double>{1.0, 1.0, 1.0, 1.0}});
	candyMap -> SetStop(0.5, qbVector<double>{std::vector<double>{1.0, 0.0, 0.0, 1.0}});
	candyMap -> SetStop(1.0, qbVector<double>{std::vector<double>{1.0, 1.0, 1.0, 1.0}});
	
	auto woodMap = std::make_shared<qbRT::Texture::ColorMap> (qbRT::Texture::ColorMap());
	woodMap -> SetStop(0.0, qbVector<double>{std::vector<double>{200.0/255.0, 150.0/255.0, 120.0/255.0, 1.0}});
	woodMap -> SetStop(0.5, qbVector<double>{std::vector<double>{100.0/255.0, 50.0/255.0, 30.0/255.0, 1.0}});
	woodMap -> SetStop(1.0, qbVector<double>{std::vector<double>{200.0/255.0, 150.0/255.0, 120.0/255.0, 1.0}});
	
    //*************************************
	// Create some textures.
    //*************************************

    auto floorTexture = std::make_shared<qbRT::Texture::Checker> (qbRT::Texture::Checker());
	floorTexture -> SetColor(qbVector<double>{std::vector<double>{0.50, 0.50, 0.50}}, qbVector<double>{std::vector<double>{0.8, 0.8, 0.2}});
	floorTexture -> SetTransform(qbVector<double>{std::vector<double>{0.0, 0.0}},
								 0.0,
								 qbVector<double>{std::vector<double>{16.0, 16.0}} );

	auto floorTexture2 = std::make_shared<qbRT::Texture::Checker> (qbRT::Texture::Checker());
	floorTexture2 -> SetTransform(qbVector<double>{std::vector<double>{0.0, 0.0}},
								  0.0,
								  qbVector<double>{std::vector<double>{16.0, 16.0}} );
	floorTexture2 -> SetColor(qbVector<double>{std::vector<double>{0.2, 0.2, 0.2, 1.0}}, qbVector<double>{std::vector<double>{0.4, 0.4, 0.4, 1.0}});



	auto sphereTexture = std::make_shared<qbRT::Texture::Checker> (qbRT::Texture::Checker());														
	sphereTexture -> SetColor(qbVector<double>{std::vector<double>{0.2, 0.2, 0.8}}, qbVector<double>{std::vector<double>{0.8, 0.8, 0.2}});
	sphereTexture -> SetTransform(qbVector<double>{std::vector<double>{0.0, 0.0}},
								  0.0,
								  qbVector<double>{std::vector<double>{16.0, 16.0}} );

    auto cylinderTexture = std::make_shared<qbRT::Texture::Checker> (qbRT::Texture::Checker());
	cylinderTexture -> SetColor(qbVector<double>{std::vector<double>{1.0, 0.0, 0.0}}, qbVector<double>{std::vector<double>{0.8, 0.8, 0.2}});
	cylinderTexture -> SetTransform(qbVector<double>{std::vector<double>{0.0, 0.0}},
									0.0,
									qbVector<double>{std::vector<double>{4.0*M_PI, 4.0}} );

	auto coneTexture = std::make_shared<qbRT::Texture::Checker> (qbRT::Texture::Checker());																
	coneTexture -> SetColor(qbVector<double>{std::vector<double>{0.2, 0.2, 0.8}}, qbVector<double>{std::vector<double>{1.0, 0.5, 0.0}});
	coneTexture -> SetTransform(qbVector<double>{std::vector<double>{0.0, 0.0}},
								0.0,
								qbVector<double>{std::vector<double>{8.0*(M_PI/2.0), 8.0}} );
    
	auto imageTexture = std::make_shared<qbRT::Texture::Image> (qbRT::Texture::Image());
    imageTexture -> LoadImage("bmp_243.bmp");
	imageTexture -> SetTransform(qbVector<double>{std::vector<double>{0.0, 0.0}},
								 0.0,
								 qbVector<double>{std::vector<double>{1.0, 1.0}});

    auto gradientTextrure = std::make_shared<qbRT::Texture::Gradient> (qbRT::Texture::Gradient());
	gradientTextrure -> SetTransform(qbVector<double>{std::vector<double>{0.0, 0.0}},
								 0.0,
								 qbVector<double>{std::vector<double>{1.0, 1.0}});
	gradientTextrure -> SetStop(0.0, qbVector<double>{std::vector<double>{1.0, 0.0, 0.0, 1.0}}); //red
	gradientTextrure -> SetStop(0.5, qbVector<double>{std::vector<double>{0.0, 1.0, 0.0, 1.0}}); //green
    gradientTextrure -> SetStop(1.0, qbVector<double>{std::vector<double>{0.0, 0.0, 1.0, 1.0}}); //blue


	auto gradientTextrure2 = std::make_shared<qbRT::Texture::Gradient> (qbRT::Texture::Gradient());
	gradientTextrure2 -> SetTransform(qbVector<double>{std::vector<double>{0.0, 0.0}},
								 0.0,
								 qbVector<double>{std::vector<double>{1.0, 1.0}});
	gradientTextrure2 -> SetStop(0.0, qbVector<double>{std::vector<double>{0.0, 1.0, 0.0, 1.0}}); //green
	gradientTextrure2 -> SetStop(0.5, qbVector<double>{std::vector<double>{1.0, 0.0, 0.0, 1.0}}); //red
    gradientTextrure2 -> SetStop(1.0, qbVector<double>{std::vector<double>{0.0, 0.0, 1.0, 1.0}}); //blue


    auto smallChecker1 = std::make_shared<qbRT::Texture::Checker> (qbRT::Texture::Checker());
	smallChecker1 -> SetColor(qbVector<double>{std::vector<double>{1.0, 1.0, 1.0, 1.0}}, qbVector<double>{std::vector<double>{0.0, 1.0, 0.0, 1.0}}); //white, green
	smallChecker1 -> SetTransform(qbVector<double>{std::vector<double>{0.0, 0.0}},
								  0.0,
								  qbVector<double>{std::vector<double>{8.0, 8.0}});


    auto smallChecker2 = std::make_shared<qbRT::Texture::Checker> (qbRT::Texture::Checker());
    smallChecker1 -> SetColor(qbVector<double>{std::vector<double>{0.0, 0.0, 0.0, 1.0}}, qbVector<double>{std::vector<double>{0.0, 0.0, 1.0, 1.0}}); //black, blue
	smallChecker1 -> SetTransform(qbVector<double>{std::vector<double>{0.0, 0.0}},
								  -M_PI/4.0,
								  qbVector<double>{std::vector<double>{8.0, 8.0}});


    auto layeredChecker = std::make_shared<qbRT::Texture::Checker> (qbRT::Texture::Checker());
    layeredChecker -> SetColor(smallChecker1, smallChecker2); 
	layeredChecker -> SetTransform(qbVector<double>{std::vector<double>{0.0, 0.0}},
								  0.0,
								  qbVector<double>{std::vector<double>{4.0, 4.0}});

    auto alphaGradiant = std::make_shared<qbRT::Texture::Gradient> (qbRT::Texture::Gradient());
	alphaGradiant -> SetTransform(qbVector<double>{std::vector<double>{0.0, 0.0}},
								 M_PI/4.0,
								 qbVector<double>{std::vector<double>{1.0, 1.0}});
	alphaGradiant -> SetStop(0.0, qbVector<double>{std::vector<double>{1.0, 0.0, 0.0, 1.0}}); //blue
	alphaGradiant -> SetStop(0.5, qbVector<double>{std::vector<double>{1.0, 1.0, 1.0, 0.0}}); //white
    alphaGradiant -> SetStop(1.0, qbVector<double>{std::vector<double>{1.0, 1.0, 0.0, 1.0}}); //yellow
	
	// Value noise texture 
	auto valNoiseTexture = std::make_shared<qbRT::Texture::BasicValNoise> (qbRT::Texture::BasicValNoise());
	valNoiseTexture -> SetColorMap(noiseMap);
	valNoiseTexture -> SetAmplitude(1.0);
	valNoiseTexture -> SetScale(60.0);

	auto valNoiseTexture2 = std::make_shared<qbRT::Texture::BasicValNoise> (qbRT::Texture::BasicValNoise());
	valNoiseTexture2 -> SetColorMap(noiseMap2);
	valNoiseTexture2 -> SetAmplitude(2.0);
	valNoiseTexture2 -> SetScale(60.0);

	auto valNoiseTexture3 = std::make_shared<qbRT::Texture::BasicValNoise> (qbRT::Texture::BasicValNoise());
	valNoiseTexture3 -> SetColorMap(noiseMap3);
	valNoiseTexture3 -> SetAmplitude(2.0);
	valNoiseTexture3 -> SetScale(30.0);

	// Marble...
	auto qbMarble = std::make_shared<qbRT::Texture::Marble> (qbRT::Texture::Marble());
	qbMarble -> SetColorMap(marbleMap);
	qbMarble -> SetAmplitude(4.0, 2.0);
	qbMarble -> SetScale(6.0, 40.0);
	qbMarble -> SetSine(1.0, 4.0);
	qbMarble -> SetMinMax(-1.0, 1.0);
	
	// Cloud
	auto qbCloud = std::make_shared<qbRT::Texture::BasicNoise> (qbRT::Texture::BasicNoise());
	qbCloud -> SetColorMap(cloudMap);
	qbCloud -> SetAmplitude(12.0);
	qbCloud -> SetScale(10);
	
	// Spiral
	auto qbSpiral = std::make_shared<qbRT::Texture::Marble> (qbRT::Texture::Marble());
	qbSpiral -> SetColorMap(candyMap);
	qbSpiral -> SetAmplitude(0.0, 0.0);
	qbSpiral -> SetScale(1.0, 10.0);
	qbSpiral -> SetSine(1.0, 8.0);
	qbSpiral -> SetMinMax(-1.0, 1.0);
	qbSpiral -> SetTransform(qbVector<double>{std::vector<double>{0.0, 0.0}}, 0.0, qbVector<double>{std::vector<double>{1.0, 1.0}});
	
	//Wood
	auto qbWood = std::make_shared<qbRT::Texture::Marble> (qbRT::Texture::Marble());
	qbWood -> SetColorMap(woodMap);
	qbWood -> SetAmplitude(8.0, 1.0);
	qbWood -> SetScale(2.0, 10.0);
	qbWood -> SetSine(1.0, 8.0);
	qbWood -> SetMinMax(-1.0, 1.0);
	qbWood -> SetTransform(qbVector<double>{std::vector<double>{0.0, 0.0}}, 0.0, qbVector<double>{std::vector<double>{1.0, 1.0}});	

    // An instance of the stone texture.
	auto stoneTexture = std::make_shared<qbRT::Texture::qbStone1> (qbRT::Texture::qbStone1());
	stoneTexture -> SetTransform(qbVector<double>{std::vector<double>{0.0, 0.0}},
								 0.0,
								 qbVector<double>{std::vector<double>{4.0, 4.0}});

	auto imageTexture2 = std::make_shared<qbRT::Texture::Image> (qbRT::Texture::Image());
	imageTexture2 -> LoadImage("Voronoi.bmp");
	imageTexture2 -> SetTransform(qbVector<double>{std::vector<double>{0.0, 0.0}},
								 0.0,
							     qbVector<double>{std::vector<double>{1.0, 1.0}});
    
	// *************************************
	// Create and setup a simple normal map.
	// *************************************

	 auto normMap1 = std::make_shared<qbRT::Normal::SimpleRough> (qbRT::Normal::SimpleRough());
	 normMap1 -> m_amplitudeScale = 0.20;

	auto normMap2 = std::make_shared<qbRT::Normal::TextureNormal> (qbRT::Normal::TextureNormal());
	normMap2 -> AssignBaseTexture(stoneTexture);
	normMap2 -> m_scale = 0.015;


	auto imageNormal = std::make_shared<qbRT::Normal::Image> (qbRT::Normal::Image());
	imageNormal -> LoadImage("Voronoi_normal.bmp");
	imageNormal -> SetTransform(qbVector<double>{std::vector<double>{0.0, 0.0}},
								0.0,
								qbVector<double>{std::vector<double>{1.0, 1.0}} );
    
    //*******************************
    // Create some materials.
	//*******************************

	//auto testMaterial1 = std::make_shared<qbRT::SimpleMaterial> (qbRT::SimpleMaterial());
    //auto testMaterial2 = std::make_shared<qbRT::SimpleMaterial> (qbRT::SimpleMaterial());
	//auto testMaterial3 = std::make_shared<qbRT::SimpleMaterial> (qbRT::SimpleMaterial());
	//auto testMaterial4 = std::make_shared<qbRT::SimpleMaterial> (qbRT::SimpleMaterial());
	//auto testMaterial5 = std::make_shared<qbRT::SimpleMaterial> (qbRT::SimpleMaterial());
	
	
	/*testMaterial1 -> m_baseColor = qbVector<double>{std::vector<double>{1.0, 1.0, 0.0}};
	testMaterial1 -> m_reflectivity = 0.50;
	testMaterial1 -> m_shininess = 10.0;

	testMaterial2 -> m_baseColor = qbVector<double>{std::vector<double>{0.0, 1.0, 0.3}};
	testMaterial2 -> m_reflectivity = 0.50;
	testMaterial2 -> m_shininess = 10.0;
	
	testMaterial3 -> m_baseColor = qbVector<double>{std::vector<double>{1.0, 0.0, 0.0}};
	testMaterial3 -> m_reflectivity = 0.50;
	testMaterial3 -> m_shininess = 10.0;

	testMaterial4 -> m_baseColor = qbVector<double>{std::vector<double>{0.7, 0.2, 0.7}};
	testMaterial4 -> m_reflectivity = 0.50;
	testMaterial4 -> m_shininess = 10.0;

	testMaterial5 -> m_baseColor = qbVector<double>{std::vector<double>{0.0, 0.7, 1.0}};
	testMaterial5 -> m_reflectivity = 0.50;
	testMaterial5 -> m_shininess = 10.0;

	floorMaterial -> m_baseColor = qbVector<double>{std::vector<double>{0.8, 0.6, 1.0}}; //Mauve
	floorMaterial -> m_reflectivity = 0.5;
	floorMaterial -> m_shininess = 0.0;*/
	

    auto silverMetal = std::make_shared<qbRT::SimpleMaterial> (qbRT::SimpleMaterial());
    silverMetal -> m_baseColor = qbVector<double>{std::vector<double>{0.5, 0.5, 0.8}};
	silverMetal -> m_reflectivity = 0.8;
	silverMetal -> m_shininess = 32.0;
	//silverMetal -> AssignTexture(coneTexture);
	
	auto goldMetal = std::make_shared<qbRT::SimpleMaterial> (qbRT::SimpleMaterial());
	goldMetal -> m_baseColor = qbVector<double>{std::vector<double>{0.96, 0.90, 0.34}};
	goldMetal -> m_reflectivity = 0.25;
	goldMetal -> m_shininess = 20.0;
	
	auto blueDiffuse = std::make_shared<qbRT::SimpleMaterial> (qbRT::SimpleMaterial());
	blueDiffuse -> m_baseColor = qbVector<double>{std::vector<double>{0.007, 0.8, 0.96}};
	blueDiffuse -> m_reflectivity = 0.8;
	blueDiffuse -> m_shininess = 32.0;
	
	auto yellowDiffuse = std::make_shared<qbRT::SimpleMaterial> (qbRT::SimpleMaterial());
	yellowDiffuse -> m_baseColor = qbVector<double>{std::vector<double>{0.8, 0.8, 0.2}};
	yellowDiffuse -> m_reflectivity = 0.5;
	yellowDiffuse -> m_shininess = 5.0;
	
	auto orangeDiffuse = std::make_shared<qbRT::SimpleMaterial> (qbRT::SimpleMaterial());
	orangeDiffuse -> m_baseColor = qbVector<double>{std::vector<double>{0.81, 0.39, 0.0}};
	orangeDiffuse -> m_reflectivity = 0.8;
	orangeDiffuse -> m_shininess = 32.0;
	orangeDiffuse -> AssignTexture(sphereTexture);
	
    auto redMetal = std::make_shared<qbRT::SimpleMaterial> (qbRT::SimpleMaterial());
	redMetal -> m_baseColor = qbVector<double>{std::vector<double>{1.0, 0.0, 0.0}};
	redMetal -> m_reflectivity = 0.5;
	redMetal -> m_shininess = 20.0;
	//redMetal -> AssignTexture(cylinderTexture);

    auto floorMaterial = std::make_shared<qbRT::SimpleMaterial> (qbRT::SimpleMaterial());
    floorMaterial -> m_baseColor = qbVector<double>{std::vector<double>{1.0, 1.0, 1.0}};
	floorMaterial -> m_reflectivity = 0.5;
	floorMaterial -> m_shininess = 0.0;
	//floorMaterial -> AssignTexture(floorTexture2);
	//floorMaterial -> AssignNormalMap(normMap2);
	floorMaterial -> AssignTexture(imageTexture2);
	floorMaterial -> AssignNormalMap(imageNormal);

    auto wallMaterial1 = std::make_shared<qbRT::SimpleMaterial> (qbRT::SimpleMaterial());
	wallMaterial1 -> m_baseColor = qbVector<double>{std::vector<double>{0.45, 0.32, 0.89}}; //purple
	wallMaterial1 -> m_reflectivity = 0.50;
	wallMaterial1 -> m_shininess = 8.0;

    auto wallMaterial2 = std::make_shared<qbRT::SimpleMaterial> (qbRT::SimpleMaterial());
	wallMaterial2 -> m_baseColor = qbVector<double>{std::vector<double>{1.0, 0.125, 0.125}};
	wallMaterial2 -> m_reflectivity = 0.50;
	wallMaterial2 -> m_shininess = 8.0;
	//wallMaterial2 -> AssignTexture(floorTexture);

    auto wallMaterial3 = std::make_shared<qbRT::SimpleMaterial> (qbRT::SimpleMaterial());
    wallMaterial3 -> m_baseColor = qbVector<double>{std::vector<double>{0.86, 0.27, 0.49}}; //pink
	wallMaterial3 -> m_reflectivity = 0.50;
	wallMaterial3 -> m_shininess = 8.0;

    auto imageMaterial = std::make_shared<qbRT::SimpleMaterial> (qbRT::SimpleMaterial());
	imageMaterial -> m_baseColor = qbVector<double>{std::vector<double>{1.0, 0.125, 0.125}};
	imageMaterial -> m_reflectivity = 0.0;
	imageMaterial -> m_shininess = 0.0;
	//imageMaterial -> AssignTexture(imageTexture);
	imageMaterial -> AssignTexture(gradientTextrure);


	auto imageMaterial2 = std::make_shared<qbRT::SimpleMaterial> (qbRT::SimpleMaterial());
	imageMaterial2 -> m_baseColor = qbVector<double>{std::vector<double>{1.0, 0.125, 0.125}};
	imageMaterial2 -> m_reflectivity = 0.0;
	imageMaterial2 -> m_shininess = 0.0;
	//imageMaterial -> AssignTexture(imageTexture);
	imageMaterial2 -> AssignTexture(gradientTextrure2);

    auto layeredMaterial = std::make_shared<qbRT::SimpleMaterial> (qbRT::SimpleMaterial());
	layeredMaterial -> m_reflectivity = 0.0;
	layeredMaterial -> m_shininess = 0.0;
	layeredMaterial -> AssignTexture(layeredChecker);
	layeredMaterial -> AssignTexture(alphaGradiant);


    auto sphereMaterial = std::make_shared<qbRT::SimpleMaterial> (qbRT::SimpleMaterial());
	sphereMaterial -> m_baseColor = qbVector<double>{std::vector<double>{0.45, 0.32, 0.89}}; //purple
	sphereMaterial -> m_reflectivity = 0.8;
	sphereMaterial -> m_shininess = 32.0;

    auto glassMaterial = std::make_shared<qbRT::SimpleRefractive> (qbRT::SimpleRefractive());
    glassMaterial -> m_baseColor = qbVector<double>{std::vector<double>{0.7, 0.7, 0.2}};
	glassMaterial -> m_reflectivity = 0.25;
	glassMaterial -> m_shininess = 32.0;
	glassMaterial -> m_translucency = 0.75;
	glassMaterial -> m_ior = 1.333;	//for water

    auto glassMaterial2 = std::make_shared<qbRT::SimpleRefractive> (qbRT::SimpleRefractive());
	glassMaterial2 -> m_baseColor = qbVector<double>{std::vector<double>{0.7, 0.7, 0.2}};
	glassMaterial2 -> m_reflectivity = 0.5;
	glassMaterial2 -> m_shininess = 35.0;
	glassMaterial2 -> m_translucency = 0.50;
	glassMaterial2 -> m_ior = 1.333;	//for water

	auto valNoiseMat = std::make_shared<qbRT::SimpleMaterial> (qbRT::SimpleMaterial());
	valNoiseMat -> m_baseColor = std::vector<double>{1.0, 1.0, 1.0};
	valNoiseMat -> m_reflectivity = 0.2;
	valNoiseMat -> m_shininess = 32.0;
	valNoiseMat -> AssignTexture(valNoiseTexture);

	auto valNoiseMat2 = std::make_shared<qbRT::SimpleMaterial> (qbRT::SimpleMaterial());
	valNoiseMat2 -> m_baseColor = std::vector<double>{1.0, 1.0, 1.0};
	valNoiseMat2 -> m_reflectivity = 0.2;
	valNoiseMat2 -> m_shininess = 32.0;
	valNoiseMat2 -> AssignTexture(valNoiseTexture2);

	auto valNoiseMat3 = std::make_shared<qbRT::SimpleMaterial> (qbRT::SimpleMaterial());
	valNoiseMat3 -> m_baseColor = std::vector<double>{1.0, 1.0, 1.0};
	valNoiseMat3 -> m_reflectivity = 0.2;
	valNoiseMat3 -> m_shininess = 32.0;
	valNoiseMat3 -> AssignTexture(valNoiseTexture3);

	auto qbMarbleMat = std::make_shared<qbRT::SimpleMaterial> (qbRT::SimpleMaterial());
	qbMarbleMat -> m_baseColor = std::vector<double>{1.0, 1.0, 1.0};
	qbMarbleMat -> m_reflectivity = 0.05;
	qbMarbleMat -> m_shininess = 32.0;
	qbMarbleMat -> AssignTexture(qbMarble);
	
	auto cloudMat = std::make_shared<qbRT::SimpleMaterial> (qbRT::SimpleMaterial());
	cloudMat -> m_baseColor = std::vector<double>{1.0, 1.0, 1.0};
	cloudMat -> m_reflectivity = 0.05;
	cloudMat -> m_shininess = 32.0;
	cloudMat -> AssignTexture(qbCloud);	
	
	auto candyMat = std::make_shared<qbRT::SimpleMaterial> (qbRT::SimpleMaterial());
	candyMat -> m_baseColor = std::vector<double>{1.0, 1.0, 1.0};
	candyMat -> m_reflectivity = 0.05;
	candyMat -> m_shininess = 32.0;
	candyMat -> AssignTexture(qbSpiral);		
	
	auto woodMat = std::make_shared<qbRT::SimpleMaterial> (qbRT::SimpleMaterial());
	woodMat -> m_baseColor = std::vector<double>{1.0, 1.0, 1.0};
	woodMat -> m_reflectivity = 0.05;
	woodMat -> m_shininess = 32.0;
	woodMat -> AssignTexture(qbWood);		


    // The stone material.
	auto stoneMat = std::make_shared<qbRT::SimpleMaterial> (qbRT::SimpleMaterial());
	stoneMat -> m_baseColor = std::vector<double>{1.0, 1.0, 1.0};
	stoneMat -> m_reflectivity = 0.35;
	stoneMat -> m_shininess = 32.0;
	stoneMat -> AssignTexture(stoneTexture);
	stoneMat -> AssignNormalMap(normMap2);	


	//***********************************
	//create and setup objects.
    //***********************************

    //################################
    // ray marching
	//################################
    auto torus_RM = std::make_shared<qbRT::RM::Torus> (qbRT::RM::Torus());
	//torus -> m_tag = "torus";
	torus_RM -> m_isVisible = true;
	torus_RM -> SetRadii(0.7, 0.3);
	torus_RM -> SetTransformMatrix(qbRT::GTform {qbVector<double>{std::vector<double>{2.25, 0.0, 0.20}},
											     qbVector<double>{std::vector<double>{-M_PI/2.0, 0.0, 0.0}},
											     qbVector<double>{std::vector<double>{0.85, 0.85, 0.85}}});
	torus_RM -> AssignMaterial(glassMaterial);


	auto Sphere_RM1 = std::make_shared<qbRT::RM::Sphere> (qbRT::RM::Sphere());
	Sphere_RM1 -> m_isVisible = true;
	Sphere_RM1 -> SetTransformMatrix(qbRT::GTform {qbVector<double>{std::vector<double>{-2.0, -0.5, 0.25}},
												  qbVector<double>{std::vector<double>{0.0, 0.0, 0.0}},
												  qbVector<double>{std::vector<double>{0.75, 0.75, 0.75}}});
	Sphere_RM1 -> AssignMaterial(glassMaterial2);

	auto Sphere_RM2 = std::make_shared<qbRT::RM::Sphere> (qbRT::RM::Sphere());
	Sphere_RM2 -> m_isVisible = true;
	Sphere_RM2 -> SetTransformMatrix(qbRT::GTform {qbVector<double>{std::vector<double>{-2.0, -1.25, -1.0}},
												  qbVector<double>{std::vector<double>{0.0, 0.0, 0.0}},
												  qbVector<double>{std::vector<double>{0.75, 0.75, 0.75}}});
	Sphere_RM2 -> AssignMaterial(glassMaterial2);

	auto Sphere_RM3 = std::make_shared<qbRT::RM::Sphere> (qbRT::RM::Sphere());
	Sphere_RM3 -> m_isVisible = true;
	Sphere_RM3 -> SetTransformMatrix(qbRT::GTform {qbVector<double>{std::vector<double>{-2.0, -2.0, 0.25}},
												  qbVector<double>{std::vector<double>{0.0, 0.0, 0.0}},
												  qbVector<double>{std::vector<double>{0.75, 0.75, 0.75}}});
	Sphere_RM3 -> AssignMaterial(glassMaterial2);


   	auto cube_RM = std::make_shared<qbRT::RM::Cube> (qbRT::RM::Cube());
	cube_RM -> m_isVisible = true;
	cube_RM -> SetTransformMatrix(qbRT::GTform {qbVector<double>{std::vector<double>{0.0, 0.0, 0.25}},
											    qbVector<double>{std::vector<double>{0.0, -M_PI/4.0, 0.0}},
											    qbVector<double>{std::vector<double>{0.50, 0.50, 0.50}}});
	cube_RM -> AssignMaterial(blueDiffuse);


    //#######################################################

	/*auto cone = std::make_shared<qbRT::Cone> (qbRT::Cone());
	cone -> SetTransformMatrix(qbRT::GTform {qbVector<double>{std::vector<double>{0.0, 0.0, -0.5}},
											 qbVector<double>{std::vector<double>{0.0, 0.0, 0.0}},
											 qbVector<double>{std::vector<double>{1.0, 1.0, 2.0}}});
	cone -> AssignMaterial(silverMetal);*/
	
	auto box = std::make_shared<qbRT::Box> (qbRT::Box());
	box -> m_isVisible = true;
	box -> SetTransformMatrix(qbRT::GTform {qbVector<double>{std::vector<double>{0.0, 0.0, 0.25}},
											 qbVector<double>{std::vector<double>{0.0, -M_PI/4.0, 0.0}},
											 qbVector<double>{std::vector<double>{0.50, 0.50, 0.50}}});
	//box -> AssignMaterial(silverMetal);
	//box ->AssignMaterial(imageMaterial);
	box ->AssignMaterial(woodMat);

	/*auto leftSphere = std::make_shared<qbRT::ObjSphere> (qbRT::ObjSphere());
	leftSphere -> SetTransformMatrix(qbRT::GTform {qbVector<double>{std::vector<double>{1.0, -2.0, 0.5}},
												   qbVector<double>{std::vector<double>{0.0, 0.0, 0.0}},
												   qbVector<double>{std::vector<double>{0.65, 0.5, 0.5}}});
	leftSphere -> AssignMaterial(blueDiffuse);*/
	
	auto rightSphere1 = std::make_shared<qbRT::ObjSphere> (qbRT::ObjSphere());
	rightSphere1 -> m_isVisible = true;
	rightSphere1 -> SetTransformMatrix(qbRT::GTform {qbVector<double>{std::vector<double>{2.0, 0.0, 0.25}},
												    qbVector<double>{std::vector<double>{0.0, 0.0, 0.0}},
													qbVector<double>{std::vector<double>{0.75, 0.75, 0.75}}});
	//rightSphere1 -> AssignMaterial(glassMaterial);
	//rightSphere1 ->AssignMaterial(imageMaterial2);
	rightSphere1 ->AssignMaterial(qbMarbleMat);

	/*auto rightSphere2 = std::make_shared<qbRT::ObjSphere> (qbRT::ObjSphere());
	rightSphere2 -> SetTransformMatrix(qbRT::GTform {qbVector<double>{std::vector<double>{0.0, 0.0, 0.50}},
												     qbVector<double>{std::vector<double>{0.0, 0.0, 0.0}},
													 qbVector<double>{std::vector<double>{0.50, 0.50, 0.50}}});
	rightSphere2 -> AssignMaterial(glassMaterial);*/
	
	auto Sphere3 = std::make_shared<qbRT::ObjSphere> (qbRT::ObjSphere());
	Sphere3 -> m_isVisible = true;
    Sphere3 -> SetTransformMatrix(qbRT::GTform {qbVector<double>{std::vector<double>{-2.0, -0.5, 0.25}},
												  qbVector<double>{std::vector<double>{0.0, 0.0, 0.0}},
												  qbVector<double>{std::vector<double>{0.75, 0.75, 0.75}}});
	//Sphere3 -> AssignMaterial(orangeDiffuse);
	//Sphere3 ->AssignMaterial(imageMaterial2);
	Sphere3  ->AssignMaterial(candyMat);

	auto Sphere11 = std::make_shared<qbRT::ObjSphere> (qbRT::ObjSphere());
	Sphere11 -> m_isVisible = true;
	Sphere11 -> SetTransformMatrix(qbRT::GTform {qbVector<double>{std::vector<double>{-2.0, -1.25, -1.0}},
												     qbVector<double>{std::vector<double>{0.0, 0.0, 0.0}},
												     qbVector<double>{std::vector<double>{0.75, 0.75, 0.75}}});
	//Sphere1 -> AssignMaterial(blueDiffuse);
	//Sphere1 ->AssignMaterial(imageMaterial2);
	Sphere11  ->AssignMaterial(cloudMat);

	auto Sphere1 = std::make_shared<qbRT::ObjSphere> (qbRT::ObjSphere());
	Sphere1 -> m_isVisible = true;
	Sphere1 -> SetTransformMatrix(qbRT::GTform {qbVector<double>{std::vector<double>{0.0, 3.0, 0.25}},
												     qbVector<double>{std::vector<double>{0.0, 0.0, 0.0}},
												     qbVector<double>{std::vector<double>{0.75, 0.75, 0.75}}});
	//Sphere1 -> AssignMaterial(blueDiffuse);
	Sphere1 ->AssignMaterial(valNoiseMat2);
	//Sphere1  ->AssignMaterial(cloudMat);

	auto Sphere2 = std::make_shared<qbRT::ObjSphere> (qbRT::ObjSphere());
	Sphere2 -> m_isVisible = true;
	Sphere2 -> SetTransformMatrix(qbRT::GTform {qbVector<double>{std::vector<double>{-2.0, -2.0, 0.25}},
												     qbVector<double>{std::vector<double>{0.0, 0.0, 0.0}},
												     qbVector<double>{std::vector<double>{0.75, 0.75, 0.75}}});
	//Sphere2 -> AssignMaterial(orangeDiffuse);
	//Sphere2 ->AssignMaterial(imageMaterial2);
	Sphere2  ->AssignMaterial(valNoiseMat);
	
	auto floor = std::make_shared<qbRT::ObjPlane> (qbRT::ObjPlane());
	floor -> m_isVisible = true;
	floor -> SetTransformMatrix(qbRT::GTform {qbVector<double>{std::vector<double>{0.0, 0.0, 1.0}},
											  qbVector<double>{std::vector<double>{0.0, 0.0, 0.0}},
											  qbVector<double>{std::vector<double>{16.0, 16.0, 1.0}}});
	floor -> AssignMaterial(floorMaterial);
	


	auto floor2 = std::make_shared<qbRT::ObjPlane> (qbRT::ObjPlane());
	floor2 -> m_isVisible = true;
	floor2 -> SetTransformMatrix(qbRT::GTform {qbVector<double>{std::vector<double>{0.0, 0.0, 0.5}},
											   qbVector<double>{std::vector<double>{0.0, 0.0, 0.0}},
											   qbVector<double>{std::vector<double>{16.0, 16.0, 1.0}}});
	floor2 -> AssignMaterial(floorMaterial);
	//floor2 -> AssignMaterial(stoneMat);
	
	auto leftWall = std::make_shared<qbRT::ObjPlane> (qbRT::ObjPlane());
	leftWall -> m_isVisible = true;
	leftWall -> SetTransformMatrix(qbRT::GTform {qbVector<double>{std::vector<double>{-4.0, 0.0, 0.0}},
										         qbVector<double>{std::vector<double>{0.0, -M_PI/2.0, -M_PI/2.0}},
												 qbVector<double>{std::vector<double>{16.0, 16.0, 1.0}}});
	leftWall -> AssignMaterial(wallMaterial1);
	//leftWall -> AssignMaterial(imageMaterial);
	
	auto backWall = std::make_shared<qbRT::ObjPlane> (qbRT::ObjPlane());
	backWall -> m_isVisible = true;
	backWall -> SetTransformMatrix(qbRT::GTform {qbVector<double>{std::vector<double>{0.0, 4.0, 0.0}},
												 qbVector<double>{std::vector<double>{-M_PI/2.0, 0.0, 0.0}},
												 qbVector<double>{std::vector<double>{16.0, 16.0, 1.0}}});
	backWall -> AssignMaterial(wallMaterial2);
	//backWall -> AssignMaterial(imageMaterial);

	auto rightWall = std::make_shared<qbRT::ObjPlane> (qbRT::ObjPlane());
	rightWall -> m_isVisible = true;
	rightWall -> SetTransformMatrix(qbRT::GTform {qbVector<double>{std::vector<double>{4.0, 0.0, 0.0}},
												 qbVector<double>{std::vector<double>{0.0, -M_PI/2.0, -M_PI/2.0}},
												 qbVector<double>{std::vector<double>{16.0, 16.0, 1.0}}});
	rightWall -> AssignMaterial(wallMaterial3);
	//rightWall -> AssignMaterial(imageMaterial);


	auto imagePlane = std::make_shared<qbRT::ObjPlane> (qbRT::ObjPlane());
	imagePlane -> m_isVisible = true;
	imagePlane-> SetTransformMatrix(qbRT::GTform {qbVector<double>{std::vector<double>{0.0, 3.0, 0.0}},
												  qbVector<double>{std::vector<double>{-M_PI/3.0, 0.0, 0.0}},
												  qbVector<double>{std::vector<double>{2.0, 2.0, 1.0}}});
	//imagePlane -> AssignMaterial(imageMaterial);
	//imagePlane -> AssignMaterial(layeredMaterial);
	imagePlane ->AssignMaterial(cloudMat);
	
	/*auto cylinder1 = std::make_shared<qbRT::Cylinder> (qbRT::Cylinder());
	cylinder1 -> SetTransformMatrix(qbRT::GTform {qbVector<double>{std::vector<double>{-1.5, -2.0, 1.0}},
												  qbVector<double>{std::vector<double>{0.0, -M_PI/2.0, 0.0}},
												  qbVector<double>{std::vector<double>{0.25, 0.25, 1.0}}});
	cylinder1 -> AssignMaterial(goldMetal);*/
	
	/*auto cylinder2 = std::make_shared<qbRT::Cylinder> (qbRT::Cylinder());
	cylinder2 -> SetTransformMatrix(qbRT::GTform {qbVector<double>{std::vector<double>{-1.0, -2.0, 0.0}},
												  qbVector<double>{std::vector<double>{0.0, M_PI/5.0, 0.0}},
												  qbVector<double>{std::vector<double>{0.25, 0.25, 1.0}}});
	cylinder2 -> AssignMaterial(redMetal);*/
	
	/*auto cone2 = std::make_shared<qbRT::Cone> (qbRT::Cone());
	cone2 -> SetTransformMatrix(qbRT::GTform {qbVector<double>{std::vector<double>{0.0, -1.0, 0.0}},
											  qbVector<double>{std::vector<double>{M_PI/4.0, 0.0, 0.0}},
											  qbVector<double>{std::vector<double>{0.5, 0.5, 1.0}}});
	cone2 -> AssignMaterial(goldMetal); */


    //*********************************************
    // Put the objects into the scene.
	//*********************************************

	//m_objectList.push_back(cone);
	//m_objectList.push_back(leftSphere);
	m_objectList.push_back(floor);
	//m_objectList.push_back(floor2);
	//m_objectList.push_back(leftWall);
	//m_objectList.push_back(backWall);
	//m_objectList.push_back(rightWall);
	//m_objectList.push_back(cylinder1);
	//m_objectList.push_back(cylinder2);
	//m_objectList.push_back(cone2);
	//m_objectList.push_back(imagePlane);
	m_objectList.push_back(Sphere1);
	m_objectList.push_back(Sphere2);
	m_objectList.push_back(Sphere3);
	m_objectList.push_back(Sphere11);
	m_objectList.push_back(rightSphere1);
	//m_objectList.push_back(rightSphere2);
	m_objectList.push_back(box);
	//m_objectList.push_back(torus_RM);
	//m_objectList.push_back(Sphere_RM1);
	//m_objectList.push_back(Sphere_RM2);
	//m_objectList.push_back(Sphere_RM3);
	//m_objectList.push_back(cube_RM);

	// Construct a test sphere.
	/*m_objectList.push_back(std::make_shared<qbRT::ObjSphere> (qbRT::ObjSphere()));
	m_objectList.push_back(std::make_shared<qbRT::ObjSphere> (qbRT::ObjSphere()));
	m_objectList.push_back(std::make_shared<qbRT::ObjSphere> (qbRT::ObjSphere()));
	m_objectList.push_back(std::make_shared<qbRT::ObjSphere> (qbRT::ObjSphere()));
	m_objectList.push_back(std::make_shared<qbRT::ObjSphere> (qbRT::ObjSphere()));*/

    // Construct a test plane.
	//m_objectList.push_back(std::make_shared<qbRT::ObjPlane> (qbRT::ObjPlane()));
	//m_objectList.at(3) -> m_baseColor = qbVector<double>{std::vector<double> {0.5, 0.5, 0.5}};
	//m_objectList.at(5) -> m_baseColor = qbVector<double>{std::vector<double> {0.5, 0.5, 0.5}};

	// Define a transform for the plane.
	/*qbRT::GTform planeMatrix;
	planeMatrix.SetTransform(qbVector<double>{std::vector<double>{0.0, 0.0, 0.75}},
							 qbVector<double>{std::vector<double>{0.0, 0.0, 0.0}},
							 qbVector<double>{std::vector<double>{4.0, 4.0, 1.0}});*/

	//m_objectList.at(3) -> SetTransformMatrix(planeMatrix);
	//m_objectList.at(5) -> SetTransformMatrix(planeMatrix);


	// Modify the spheres.
    /*qbRT::GTform testMatrix1, testMatrix2, testMatrix3, testMatrix4, testMatrix5;
	testMatrix1.SetTransform(qbVector<double>{std::vector<double>{-2.0, 2.0, 0.0}}, //translate
					         qbVector<double>{std::vector<double>{0.0, 0.0, 0.0}}, //rotate
					         qbVector<double>{std::vector<double>{0.5, 0.5, 0.65}}); //scale

	testMatrix4.SetTransform(qbVector<double>{std::vector<double>{-1.75, 9.0, 0.0}}, 
					         qbVector<double>{std::vector<double>{0.0, 0.0, 0.0}}, 
					         qbVector<double>{std::vector<double>{0.5, 0.5, 0.5}}); 


    testMatrix2.SetTransform(qbVector<double>{std::vector<double>{0.0, 0.0, 0.0}},
					         qbVector<double>{std::vector<double>{0.0, 0.0, 0.0}},
					         qbVector<double>{std::vector<double>{0.5, 0.5, 0.5}});

	testMatrix5.SetTransform(qbVector<double>{std::vector<double>{1.75, 9.0, 0.0}},
					         qbVector<double>{std::vector<double>{0.0, 0.0, 0.0}},
					         qbVector<double>{std::vector<double>{0.5, 0.5, 0.5}});

	
	testMatrix3.SetTransform(qbVector<double>{std::vector<double>{2.25, 2.0, 0.0}}, //translate
					         qbVector<double>{std::vector<double>{0.0, 0.0, 0.0}}, //rotate
					         qbVector<double>{std::vector<double>{0.65, 0.5, 0.5}}); //scale
														
	
    m_objectList.at(0) -> SetTransformMatrix(testMatrix1);
	m_objectList.at(1) -> SetTransformMatrix(testMatrix4);
	m_objectList.at(2) -> SetTransformMatrix(testMatrix2);
	m_objectList.at(3) -> SetTransformMatrix(testMatrix5);
	m_objectList.at(4) -> SetTransformMatrix(testMatrix3);*/

	//m_objectList.at(0) -> SetTransformMatrix(testMatrix1);
	//m_objectList.at(1) -> SetTransformMatrix(testMatrix2);
	//m_objectList.at(2) -> SetTransformMatrix(testMatrix3);

    //m_objectList.at(0) -> m_baseColor = qbVector<double>{std::vector<double>{1.0, 1.0, 0.0}}; //Yellow
	//m_objectList.at(1) -> m_baseColor = qbVector<double>{std::vector<double>{1.0, 0.0, 1.0}}; //Purple
	//m_objectList.at(2) -> m_baseColor = qbVector<double>{std::vector<double>{0.0, 0.7, 1.0}}; //Aqua

   
	/*m_objectList.at(0) -> m_baseColor = qbVector<double>{std::vector<double>{1.0, 1.0, 0.0}}; //Yellow
	m_objectList.at(1) -> m_baseColor = qbVector<double>{std::vector<double>{0.0, 1.0, 0.3}}; //Green
	m_objectList.at(2) -> m_baseColor = qbVector<double>{std::vector<double>{1.0, 0.0, 0.0}}; //Red
	m_objectList.at(3) -> m_baseColor = qbVector<double>{std::vector<double>{0.7, 0.2, 0.7}}; //Bright Purple
	m_objectList.at(4) -> m_baseColor = qbVector<double>{std::vector<double>{0.0, 0.7, 1.0}}; //Aqua */

	// Assign materials to objects.
	/*m_objectList.at(0) -> AssignMaterial(testMaterial1);
	m_objectList.at(1) -> AssignMaterial(testMaterial2);
	m_objectList.at(2) -> AssignMaterial(testMaterial3);
	m_objectList.at(3) -> AssignMaterial(testMaterial4);
	m_objectList.at(4) -> AssignMaterial(testMaterial5);
	m_objectList.at(5) -> AssignMaterial(floorMaterial);*/

	// Construct a test light.
	/*m_lightList.push_back(std::make_shared<qbRT::PointLight> (qbRT::PointLight()));
	m_lightList.at(0) -> m_location = qbVector<double> {std::vector<double> {5.0, -10.0, -5.0}};
	m_lightList.at(0) -> m_color = qbVector<double> {std::vector<double> {0.0, 0.0, 1.0}}; //blue

	m_lightList.push_back(std::make_shared<qbRT::PointLight> (qbRT::PointLight()));
	m_lightList.at(1) -> m_location = qbVector<double> {std::vector<double> {-5.0, -10.0, -5.0}}; 
	m_lightList.at(1) -> m_color = qbVector<double> {std::vector<double> {1.0, 0.0, 0.0}}; //red
	
	m_lightList.push_back(std::make_shared<qbRT::PointLight> (qbRT::PointLight()));
	m_lightList.at(2) -> m_location = qbVector<double> {std::vector<double> {0.0, -10.0, -5.0}};
	m_lightList.at(2) -> m_color = qbVector<double> {std::vector<double> {0.0, 1.0, 0.0}}; //green */
 
    //******************************************
    // Construct and setup the lights.
	//******************************************

    /*m_lightList.push_back(std::make_shared<qbRT::PointLight> (qbRT::PointLight()));
	m_lightList.at(0) -> m_location = qbVector<double> {std::vector<double> {3.0, -10.0, -5.0}};
	m_lightList.at(0) -> m_color = qbVector<double> {std::vector<double> {1.0, 1.0, 1.0}};
	m_lightList.at(0) -> m_intensity = 4.0;
	
	m_lightList.push_back(std::make_shared<qbRT::PointLight> (qbRT::PointLight()));
	m_lightList.at(1) -> m_location = qbVector<double> {std::vector<double> {0.0, -10.0, -5.0}};
	m_lightList.at(1) -> m_color = qbVector<double> {std::vector<double> {1.0, 1.0, 1.0}};
	m_lightList.at(1) -> m_intensity = 2.0; */

	auto leftLight = std::make_shared<qbRT::PointLight> (qbRT::PointLight());
	leftLight -> m_location = qbVector<double> {std::vector<double> {-8.0, -20.0, -10.0}};
	leftLight -> m_color = qbVector<double> {std::vector<double> {1.0, 1.0, 1.0}};
	leftLight -> m_intensity = 4.0;
	
	auto rightLight = std::make_shared<qbRT::PointLight> (qbRT::PointLight());
	rightLight -> m_location = qbVector<double> {std::vector<double> {8.0, -20.0, -10.0}};
	rightLight -> m_color = qbVector<double> {std::vector<double> {1.0, 1.0, 1.0}};
	rightLight -> m_intensity = 6.0;
	
	auto topLight = std::make_shared<qbRT::PointLight> (qbRT::PointLight());
	topLight -> m_location = qbVector<double> {std::vector<double> {0.0, 0.0, -10.0}};
	topLight -> m_color = qbVector<double> {std::vector<double> {1.0, 1.0, 1.0}};
	topLight -> m_intensity = 4.0;
	
	m_lightList.push_back(leftLight);
	m_lightList.push_back(rightLight);
	//m_lightList.push_back(topLight);


}

// Function to perform the rendering.
bool qbRT::Scene::Render(qbImage &outputImage)
{
	// Get the dimensions of the output image.
	int xSize = outputImage.GetXSize();
	int ySize = outputImage.GetYSize();
	
	// Loop over each pixel in our image.
	qbRT::Ray cameraRay;
	qbVector<double> intPoint			(3);
	qbVector<double> localNormal	(3);
	qbVector<double> localColor		(3);
	double xFact = 1.0 / (static_cast<double>(xSize) / 2.0);
	double yFact = 1.0 / (static_cast<double>(ySize) / 2.0);
	double minDist = 1e6;
	double maxDist = 0.0;
	for (int y=0; y<ySize; ++y)
	{
		// Display progress.
		std::cout << "Processing line " << y << " of " << ySize << "." << " \r";
		std::cout.flush();
		
		for (int x=0; x<xSize; ++x)
		{
			// Normalize the x and y coordinates.
			double normX = (static_cast<double>(x) * xFact) - 1.0;
			double normY = (static_cast<double>(y) * yFact) - 1.0;
			
			// Generate the ray for this pixel.
			m_camera.GenerateRay(normX, normY, cameraRay);
			
			// Test for intersections with all objects in the scene.
			std::shared_ptr<qbRT::ObjectBase> closestObject;
			qbVector<double> closestIntPoint		{3};
			qbVector<double> closestLocalNormal	{3};
			qbVector<double> closestLocalColor	{3};
			bool intersectionFound = CastRay(cameraRay, closestObject, closestIntPoint, closestLocalNormal, closestLocalColor);
			
			/* Compute the illumination for the closest object, assuming that there
				was a valid intersection. */
			if (intersectionFound)
			{
				// Check if the object has a material.
				if (closestObject -> m_hasMaterial)
				{
					// Use the material to compute the color.
					qbRT::MaterialBase::m_reflectionRayCount = 0;
					qbVector<double> color = closestObject -> m_pMaterial -> ComputeColor(m_objectList, m_lightList,closestObject, closestIntPoint,
																						   closestLocalNormal, cameraRay);
					outputImage.SetPixel(x, y, color.GetElement(0), color.GetElement(1), color.GetElement(2));
				}
				else
				{
					// Use the basic method to compute the color.
					qbVector<double> matColor = qbRT::MaterialBase::ComputeDiffuseColor(m_objectList, m_lightList,
																						closestObject, closestIntPoint,
																						closestLocalNormal, closestObject->m_baseColor);
					outputImage.SetPixel(x, y, matColor.GetElement(0), matColor.GetElement(1), matColor.GetElement(2));
				}
			}
		}
	}

	std::cout << std::endl;
	return true;
}


bool qbRT::Scene::CastRay(qbRT::Ray &castRay, std::shared_ptr<qbRT::ObjectBase> &closestObject,
						  qbVector<double> &closestIntPoint, qbVector<double> &closestLocalNormal,
						  qbVector<double> &closestLocalColor)
{
    qbVector<double> intPoint		{3};
	qbVector<double> localNormal	{3};
	qbVector<double> localColor		{3};
	double minDist = 1e6;
	bool intersectionFound = false;
	for (auto currentObject : m_objectList)
	{
		bool validInt = currentObject -> TestIntersection(castRay, intPoint, localNormal, localColor);
		
		// If we have a valid intersection.
		if (validInt)
		{
			// Set the flag to indicate that we found an intersection.
			intersectionFound = true;
					
			// Compute the distance between the camera and the point of intersection.
			double dist = (intPoint - castRay.m_point1).norm();
					
			/* If this object is closer to the camera than any one that we have
				seen before, then store a reference to it. */
			if (dist < minDist)
			{
				minDist = dist;
				closestObject = currentObject;
				closestIntPoint = intPoint;
				closestLocalNormal = localNormal;
				closestLocalColor = localColor;
			}
		}
	}
	
	return intersectionFound;

}
			