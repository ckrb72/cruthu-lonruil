#include <stdio.h>
#include <stdlib.h>
#include <glad/glad.h>
#include "renderer/window.h"
#include "event/events.h"
#include "utils/cl_file.h"
#include <string.h>

struct test
{
    int a;
    float b;
};

int main()
{

    struct test test_var = { 123, 0.445 };

    if(!clWriteFile((void*)&test_var, sizeof(test_var), 1, "./test.txt", CL_WRITE_OVERWRITE))
    {
        printf("Failed to write to file!\n");
        return -1;
    }


    // Read binary from file
    unsigned char* bytes = clReadFileBinary("./test.txt");

    // Create new struct for testing
    struct test read_var;

    // Extract int
    read_var.a = *(int*)bytes;
    bytes += sizeof(int);

    // Extract float
    read_var.b = *(float*)bytes;

    // Print values to make sure they are correct
    printf("%d\n%f", read_var.a, read_var.b);

    window_t* window = clCreateWindow(800, 600, "cruthu lonruil");


    while(!clWindowShouldClose(window))
    {
        clPollEvents();

        glClear(GL_COLOR_BUFFER_BIT);

        glClearColor(0.3, 0.3, 0.3, 1.0);

        clSwapBuffers(window);
    }

    clDestroyWindow(window);

}