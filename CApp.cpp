#include "CApp.h"
#include "qbVector.h"

// The constructor (default)
CApp::CApp()
{
   isRunning = true;
   pWindow = NULL;
   pRenderer = NULL;

}


bool CApp::OnInit()
{
  if (SDL_Init(SDL_INIT_EVERYTHING < 0))
  {
    return false;
  }

 // int xSize = 1280;
  //int ySize = 720;

  int xSize = 1260;
  int ySize = 700;

  //pWindow = SDL_CreateWindow("Ray Tracing", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WIDTH, HEIGHT, SDL_WINDOW_SHOWN);

  pWindow = SDL_CreateWindow("Ray Tracing", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, xSize, ySize, SDL_WINDOW_SHOWN);

  
  	if (pWindow != NULL)
	{
		// Initialise the renderer.
		pRenderer = SDL_CreateRenderer(pWindow, -1, 0);
		
		// Initialise the qbImage instance.
		//m_image.Initialize(WIDTH, HEIGHT, pRenderer);
		m_image.Initialize(xSize, ySize, pRenderer);
		
		// Create some colour variations.
		/*for (int x=0; x<WIDTH; ++x)
		{
			for (int y=0; y<HEIGHT; ++y)
			{
				double red = (static_cast<double>(x)/800.0) * 255.0;
				double green = (static_cast<double>(y)/600.0) * 255.0;
				m_image.SetPixel(x, y, red, green, 0.0);
			}
		} */

       // Test the camera class.
		/*qbRT::Camera testCamera;
		testCamera.SetPosition(qbVector<double>(std::vector<double>{0.0, 0.0, 0.0}));
		testCamera.SetLookAt(qbVector<double>(std::vector<double>{0.0, 2.0, 0.0}));
		testCamera.SetUp(qbVector<double>(std::vector<double>{0.0, 0.0, 1.0}));
		testCamera.SetLength(1.0);
		testCamera.SetHorzSize(1.0);
		testCamera.SetAspect(1.0);
		testCamera.UpdateCameraGeometry();
		
		// Get the screen centre and U,V vectors and display.
		auto screenCentre = testCamera.GetScreenCentre();
		auto screenU = testCamera.GetU();
		auto screenV = testCamera.GetV();
		
		// And display to the terminal.
		std::cout << "Camera screen centre:" << std::endl;
		PrintVector(screenCentre);
		std::cout << "\nCamera U vector:" << std::endl;
		PrintVector(screenU);
		std::cout << "\nCamera V vector:" << std::endl;
		PrintVector(screenV);*/

		// Set the background color to white.
		SDL_SetRenderDrawColor(pRenderer, 255, 255, 255, 255);
		SDL_RenderClear(pRenderer);
		
		// Render the scene.
		m_scene.Render(m_image);

		// Setup a texture.
		/*qbRT::Texture::Checker testTexture;
		testTexture.SetTransform(qbVector<double>{std::vector<double>{0.0, 0.0}},
								M_PI/4.0,
								 qbVector<double>{std::vector<double>{4.0, 4.0}}	);
															
		// Render the texture.
		for (int y=0; y<ySize; ++y)
		{
			for (int x=0; x<xSize; ++x)
			{
				// Compute u,v
				double u = (static_cast<double>(x) / (static_cast<double>(xSize) / 2.0)) - 1.0;
				double v = (static_cast<double>(y) / (static_cast<double>(ySize) / 2.0)) - 1.0;
				qbVector<double> uvCoords {std::vector<double> {u, v}};
				
				// Get the color from the texture.
				qbVector<double> pixelColor = testTexture.GetColor(uvCoords);
				
				// Update this pixel of the image.
				m_image.SetPixel(x, y, pixelColor.GetElement(0), pixelColor.GetElement(1), pixelColor.GetElement(2));
			}
		}*/
		
		// Display the image.
		m_image.Display();
		
		// Show the result.
		SDL_RenderPresent(pRenderer);
		
	}
	else
	{
		return false;
	}
	
	return true;
}

int CApp::OnExecute()
{
    SDL_Event event;
	
	if (OnInit() == false)
	{
		return -1;
	}
	
	while (isRunning)
	{
		while (SDL_PollEvent(&event) != 0)
		{
			OnEvent(&event);
		}
		
		OnLoop();
		OnRender();
	}
	
	OnExit();
	return 0;  

}

void CApp::OnEvent(SDL_Event *event)
{
     	if (event->type == SDL_QUIT)
	{
		isRunning = false;
	}

}


void CApp::OnLoop()
{
   

}

void CApp::OnRender()
{
   // Set the background colour to white.
	//SDL_SetRenderDrawColor(pRenderer, 255, 255, 255, 255);
	//SDL_RenderClear(pRenderer);

	// Render the scene.
	//m_scene.Render(m_image);
	
	// Display the image.
	//m_image.Display();
	
	// Show the result.
	//SDL_RenderPresent(pRenderer);

}

void CApp::OnExit()
{
    // Tidy up SDL2 stuff.
	SDL_DestroyRenderer(pRenderer);
	SDL_DestroyWindow(pWindow);
	pWindow = NULL;
	SDL_Quit();

}

// PRIVATE FUNCTIONS.
void CApp::PrintVector(const qbVector<double> &inputVector)
{
	int nRows = inputVector.GetNumDims();
	for (int row = 0; row<nRows; ++row)
  {
       std::cout << std::fixed << std::setprecision(3) << inputVector.GetElement(row) << std::endl;
	
  } 	
}



