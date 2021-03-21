/**
 * @file main_window.hpp
 * @author @Aalexdev (aaleex394@gmail.com)
 * @brief prymary window functions
 * @version 1.0.1
 * 
 * @copyright (c) 2021 Aalex
 * 
 * MIT License
 *
 *  Copyright (c) 2021 Aalex
 *
 *  Permission is hereby granted, free of charge, to any person obtaining a copy
 *  of this software and associated documentation files (the "Software"), to deal
 *  in the Software without restriction, including without limitation the rights
 *  to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 *  copies of the Software, and to permit persons to whom the Software is
 *  furnished to do so, subject to the following conditions: 
 * 
 * The above copyright notice and this permission notice shall be included in all
 *  copies or substantial portions of the Software.
 * 
 *  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 *  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 *  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 *  AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 *  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 *  OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 *  SOFTWARE.
 *
 */

#ifndef __MAIN_WINDOW__
#define __MAIN_WINDOW__

    #include <SDL2/SDL.h>
    #include "main.hpp"
    
    /**
     * @brief reset the window and the renderer of SDL
     * 
     * @param title the title of the window
     * @param Xpos the x position of the window
     * @param Ypos the y position of the window
     * @param width the width of the window
     * @param height the height of the window
     * @param flags flags of the window
     * @return return true if reset or created, false on error
     */
    bool resteWindow(const char* title, int Xpos, int Ypos, int width, int height, int flags);

    /**
     * @brief destroy the window and the renderer
     * 
     */
    void clearWindow(void);

#endif