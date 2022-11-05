// compile using this command
// g++ -std=c++20 main.cpp -lglfw -lGL -lglut -lGLEW -pthread -o test

#include<thread>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
using namespace std;

// Include GLEW
#include <GL/glew.h>
// Include GLFW
#include <GLFW/glfw3.h>
// Include GLM: a library for 3D mathematics
#include <glm/glm.hpp>
#include <math.h>
using namespace glm;

// ----------------------------------------------------------------
auto randomF() {
    struct re { 
        float a;
    float b;
    float c;
    };
    srand((unsigned int) time (NULL)); //activates the generator
    float r = ((float) rand() / (RAND_MAX));  
    r = floorf(r * 10) / 10;
    float r1 = ((float) rand() / (RAND_MAX));  
    r1 = floorf(r1 * 10) / 10;
    float r2 = ((float) rand() / (RAND_MAX));  
    r2 = floorf(r2 * 10) / 10;
    return re {r,r1,r2};
}

// ----------------------------------------------------------------
// ------------------shapes----------------------------------------
// ----------------------------------------------------------------

// each shape func take 2 inputs color and size
void triangle(int color ,float size ,int number){
    //----- same for each func -------
    auto [r,g,b] = randomF();
    float tx = 0;
    float ty = 0;
    if (color == 1) 
        glColor3f(1.0f, 0.0f, 0.0f);
    else if (color == 2)
        glColor3f(0.0f, 1.0f, 0.0f);
    else if (color == 3)
        glColor3f(0.0f, 0.0f, 1.0f);
    else if (color == 4)
        glColor3f(r, g, b);    

    glScalef(size,size,0.0f);
    
    if (number > 0)
        for (int i = 0; i < number; i++) {
            
            glTranslatef(tx,ty,0);

            glBegin(GL_POLYGON);                // Begin drawing the Traingle
    
            glVertex3f( -0.1f, 0.1f, 0); 
            glVertex3f( 0.0f, 0.4f, 0); 
            glVertex3f( 0.1f, 0.1f, 0);

            glEnd();

            tx += 0.2f;
            ty += 0.2f;
        }    

    else    
    //---------------------------------
        // start drawing the shape
        glBegin(GL_POLYGON);                // Begin drawing the Traingle
    
            glVertex3f( -0.1f, 0.1f, 0); 
            glVertex3f( 0.0f, 0.4f, 0); 
            glVertex3f( 0.1f, 0.1f, 0);

        glEnd();

}

void circle(){
    float j, k;
        GLfloat x, y, z, a = 0.60, b = 0.60, c = 1.3;
        GLfloat twicePi = 2.0f * 3.14;
        glColor3f(0.2f, 0.0f, 0.7f);

        glBegin(GL_POLYGON);
        for (k = 0; k <= 3.14; k += 0.01) {
            for (j = 0; j <= twicePi; j += 0.01) {
                x = (a * sin(k) * cos(j));
                y = (b * sin(k) * sin(j));
                z = c * cos(k);
                glVertex3f(x, y, z);
            }
        }       
        glEnd();
}

// TODO add square shape func

void rectangle(int color ,float size ,int number){
    //----- same for each func -------
    auto [r,g,b] = randomF();
    float tx = 0;
    float ty = 0;
    if (color == 1) 
        glColor3f(1.0f, 0.0f, 0.0f);
    else if (color == 2)
        glColor3f(0.0f, 1.0f, 0.0f);
    else if (color == 3)
        glColor3f(0.0f, 0.0f, 1.0f);
    else if (color == 4)
        glColor3f(r, g, b);    

    glScalef(size,size,0.0f);
    
    if (number > 0)
        for (int i = 0; i < number; i++) {
            
            glTranslatef(tx,ty,0);

            glBegin(GL_POLYGON);                // Begin drawing the rectangle

                glVertex3f( -0.1f, 0.1f, 0);
                glVertex3f( -0.1f, 0.4f, 0);
                glVertex3f( 0.3f, 0.4f, 0);
                glVertex3f( 0.3f, 0.1f, 0);
            
            glEnd();

            tx += 0.2f;
            ty += 0.2f;
        }    

    else    
    //---------------------------------
        // start drawing the shape
        glBegin(GL_POLYGON);                // Begin drawing the rectangle
    
            glVertex3f( -0.1f, 0.1f, 0);
            glVertex3f( -0.1f, 0.4f, 0);
            glVertex3f( 0.3f, 0.4f, 0);
            glVertex3f( 0.3f, 0.1f, 0);

        glEnd();

}

// ----------------------------------------------------------------
// ------------------draw Func-------------------------------------
// ----------------------------------------------------------------

int draw(int color,float size,int number,void (*func)(int,float,int))
{
    // Initialise GLFW
    if (!glfwInit())
    {
        fprintf(stderr, "Error: unable to start GLFW\n");
        return -1;
    }

    glfwWindowHint(GLFW_SAMPLES, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 2);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);

    // Create a window and create its OpenGL context 

    // Change size of the window 
    GLFWwindow* window = glfwCreateWindow(800, 600, "Omer khan 391007603", NULL, NULL);

    if (window == NULL) {
        fprintf(stderr, "Unable to open GLFW window.\n");
        glfwTerminate();
        return -2;
    }

    glfwMakeContextCurrent(window);

    // Initialize GLEW
    if (glewInit() != GLEW_OK) {
        fprintf(stderr, "Unable to start GLEW\n");
        return -3;
    }

    // Ensure we can capture the escape key being pressed below
    glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);

    do {

        int width, height;
        glfwGetFramebufferSize(window, &width, &height);
        float ratio = width / (float)height;

        glViewport(0, 0, width, height);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        glOrtho(-ratio, ratio, -3.f, 3.f, 1.f, -1.f);

        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();
        glRotatef(0.0, 0.0, 0.0, 0.0);

        // Clear the screen
        glClear(GL_COLOR_BUFFER_BIT);

    // ----------------here draw---------------
        func(color,size,number);
        

    // --------------------------------------
        // Swap buffers
        glfwSwapBuffers(window);
        glfwPollEvents();

    }
    // Check if the ESC key was pressed or the window was closed
    while (glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS &&
        glfwWindowShouldClose(window) == 0);

    // Close OpenGL window and terminate GLFW
    glfwTerminate();

    return 0;
}

int main( void )
{
    int mLOOP = 1;
    int sLOOP = 1;
    int cLOOP = 1;

    int mSwitch;
    int sSwitch;
    
    int cSelect;
    float sSelect;
    int nSelect;
    int YorN;

    while (mLOOP == 1){
        sLOOP = 1;
        cout << "---------------------- \n";
        cout << "select opreation to do \n";
        cout << "---------------------- \n";
        cout << "(1) draw one shape \n";
        cout << "(2) draw multiple shapes \n";
        cout << "(3) exit \n";
        cin >> mSwitch;

        switch (mSwitch)
        {
        case 1: // select one shape opreation 
            while (sLOOP == 1){
                sLOOP = 1;
                cout << "---------------------- \n";
                cout << "select shape \n";
                cout << "---------------------- \n";
                cout << "(1) triangle \n";
                cout << "(2) circle \n";
                cout << "(3) square \n";
                cout << "(4) rectangle \n";
                cout << "(5) exit \n";
                cin >> sSwitch;
                switch (sSwitch)
                {
                case 1: // select triangle shape opreation
                    while (cLOOP == 1){
                        cout << "---------------------- \n";
                        cout << "select shape color \n";
                        cout << "---------------------- \n";
                        cout << "(1) red \n";
                        cout << "(2) green \n";
                        cout << "(3) blue \n";
                        cout << "(4) random \n";
                        cin >> cSelect;

                        if(cSelect < 1 || cSelect > 4){
                            cout << "----------------------------- \n"; 
                            cout << "Please enter a valid color\n";
                            cout << "----------------------------- \n"; 
                            continue;
                        }

                        cout << "---------------------- \n";
                        cout << "enter shape size \n";
                        cout << "enter postive number  \n";
                        cout << "high num = bigger shape  \n";
                        cout << "---------------------- \n";  
                        cin >> sSelect;

                        if(sSelect < 1){
                            cout << "----------------------------- \n"; 
                            cout << "Please enter a valid size\n";
                            cout << "----------------------------- \n"; 
                            continue;
                        }

                        std::thread thread (draw,cSelect,sSelect,0,triangle); // just change shape func name
                        thread.detach();
                        cout << "---------------------- \n";
                        cout << "draw shape with another color ? \n";
                        cout << "---------------------- \n";
                        cout << "(1) yes \n";
                        cout << "(2) no \n";
                        cin >> YorN;
                        if (thread.joinable()){
                            thread.join();}
                         
                        if (YorN == 2){
                            cLOOP = 0;
                            break;
                        }
                        else
                        {
                            cLOOP = 1;
                        }
                        }
                case 2:
                    // TODO add circle logic here
                    break;
                case 3:
                    // TODO add square logic here
                    break;
                case 4:
                    
                    while (cLOOP == 1){
                        cout << "---------------------- \n";
                        cout << "select shape color \n";
                        cout << "---------------------- \n";
                        cout << "(1) red \n";
                        cout << "(2) green \n";
                        cout << "(3) blue \n";
                        cout << "(4) random \n";
                        cin >> cSelect;

                        if(cSelect < 1 || cSelect > 4){
                            cout << "---------------------------- \n"; 
                            cout << "Please enter a valid color\n";
                            cout << "---------------------------- \n"; 
                            continue;
                        }

                        cout << "---------------------- \n";
                        cout << "enter shape size \n";
                        cout << "enter postive number  \n";
                        cout << "high num = bigger shape  \n";
                        cout << "---------------------- \n";  
                        cin >> sSelect;

                        if(sSelect < 1){
                            cout << "-------------------------- \n"; 
                            cout << "Please enter a valid size\n";
                            cout << "-------------------------- \n"; 
                            continue;
                        }

                        std::thread thread (draw,cSelect,sSelect,0,rectangle); // just change shape func name
                        thread.detach();
                        cout << "---------------------- \n";
                        cout << "draw shape with another color ? \n";
                        cout << "---------------------- \n";
                        cout << "(1) yes \n";
                        cout << "(2) no \n";
                        cin >> YorN;
                        if (thread.joinable()){
                            thread.join();}
                         
                        if (YorN == 2){
                            cLOOP = 0;
                            break;
                        }
                        else
                        {
                            cLOOP = 1;
                        }
                        }

                    break;                                               
                case 5: 
                    sLOOP = 0;
                    break;
                default:
                    cout << "Please enter number between 1 and 5 \n";
                    break;
                }
            } 
        case 2: // select multiple shape opreation
            while (sLOOP == 1){
                sLOOP = 1;
                cout << "---------------------- \n";
                cout << "select shape \n";
                cout << "---------------------- \n";
                cout << "(1) triangle \n";
                cout << "(2) circle \n";
                cout << "(3) square \n";
                cout << "(4) rectangle \n";
                cout << "(5) exit \n";
                cin >> sSwitch;
                switch (sSwitch)
                {
                case 1: // select triangle shape opreation
                    while (cLOOP == 1){
                        //TODO add validator for cSelect , sSelect 
                        cout << "---------------------- \n";
                        cout << "select shape color \n";
                        cout << "---------------------- \n";
                        cout << "(1) red \n";
                        cout << "(2) green \n";
                        cout << "(3) blue \n";
                        cout << "(4) random \n";
                        cin >> cSelect;

                        if(cSelect < 1 || cSelect > 4){
                            cout << "---------------------------- \n"; 
                            cout << "Please enter a valid color\n";
                            cout << "---------------------------- \n"; 
                            continue;
                        }

                        cout << "---------------------- \n";
                        cout << "enter shape size \n";
                        cout << "enter postive number  \n";
                        cout << "high num = bigger shape  \n";
                        cout << "---------------------- \n";  
                        cin >> sSelect;

                        if(sSelect < 1){
                            cout << "----------------------------- \n"; 
                            cout << "Please enter a valid size\n";
                            cout << "----------------------------- \n"; 
                            continue;
                        }

                        cout << "---------------------- \n";
                        cout << "enter number of shapes \n";
                        cout << "enter postive number  \n";
                        cout << "---------------------- \n";  
                        cin >> nSelect;

                        if(nSelect < 1){
                            cout << "----------------------------- \n"; 
                            cout << "Please enter a valid number\n";
                            cout << "----------------------------- \n"; 
                            continue;
                        }

                        std::thread thread (draw,cSelect,sSelect,nSelect,triangle); // just change shape func name
                        thread.detach();
                        cout << "---------------------- \n";
                        cout << "draw shape with another color ? \n";
                        cout << "---------------------- \n";
                        cout << "(1) yes \n";
                        cout << "(2) no \n";
                        cin >> YorN;
                        if (thread.joinable()){
                            thread.join();}
                         
                        if (YorN == 2){
                            cLOOP = 0;
                            break;
                        }
                        else
                        {
                            cLOOP = 1;
                        }
                        }
                case 2:
                    // TODO add circle logic here
                    break;
                case 3:
                    // TODO add square logic here
                    break;
                case 4:
                    
                    while (cLOOP == 1){
                        //TODO add validator for cSelect , sSelect 
                        cout << "---------------------- \n";
                        cout << "select shape color \n";
                        cout << "---------------------- \n";
                        cout << "(1) red \n";
                        cout << "(2) green \n";
                        cout << "(3) blue \n";
                        cout << "(4) random \n";
                        cin >> cSelect;

                        if(cSelect < 1 || cSelect > 4){
                            cout << "----------------------------- \n"; 
                            cout << "Please enter a valid color\n";
                            cout << "----------------------------- \n"; 
                            continue;
                        }

                        cout << "---------------------- \n";
                        cout << "enter shape size \n";
                        cout << "enter postive number  \n";
                        cout << "high num = bigger shape  \n";
                        cout << "---------------------- \n";  
                        cin >> sSelect;

                        if(sSelect < 1){
                            cout << "----------------------------- \n"; 
                            cout << "Please enter a valid size\n";
                            cout << "----------------------------- \n"; 
                            continue;
                        }

                        cout << "---------------------- \n";
                        cout << "enter number of shapes \n";
                        cout << "enter postive number  \n";
                        cout << "---------------------- \n";  
                        cin >> nSelect;

                        if(nSelect < 1){
                            cout << "----------------------------- \n"; 
                            cout << "Please enter a valid number\n";
                            cout << "----------------------------- \n"; 
                            continue;
                        }
                        
                        std::thread thread (draw,cSelect,sSelect,nSelect,rectangle); // just change shape func name
                        thread.detach();
                        cout << "---------------------- \n";
                        cout << "draw shape with another color ? \n";
                        cout << "---------------------- \n";
                        cout << "(1) yes \n";
                        cout << "(2) no \n";
                        cin >> YorN;
                        if (thread.joinable()){
                            thread.join();}
                         
                        if (YorN == 2){
                            cLOOP = 0;
                            break;
                        }
                        else
                        {
                            cLOOP = 1;
                        }
                        }

                    
                    break;                                               
                case 5: 
                    sLOOP = 0;
                    break;
                default:
                    cout << "Please enter number between 1 and 5 \n";
                    break;
                }
            }
        case 3: // exit from the program
            mLOOP = 0;
            break;
        default:
            cout << "Please enter number between 1 and 3 \n";
            break;
        }
    }
}


