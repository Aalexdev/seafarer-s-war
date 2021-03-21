/**
 * @file island.hpp
 * @author @Aalexdev (aalex3984@gmail.com)
 * @brief 
 * @version 0.1
 * @date 2021-02-16
 * 
 * @copyright Copyright (c) 2021 Aalex
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
 */

/**
 * @file entity.hpp
 * 
 * Header file for Island, Island type class and methode managment
 * 
 */
#ifndef __ISLAND__
#define __ISLAND__

    #include <iostream>
    #include <SDL2/SDL.h>
    #include <vector>

    #include "api/io/xml.hpp"
    
    class Island_type{
        public:
            /**
             * @brief Construct a new Island_type object
             * 
             */
            Island_type(void);
            
            /**
             * @brief Destroy the Island_type object
             * 
             */
            ~Island_type();

            /**
             * @brief load the island from a xml node
             * 
             * @param node the xml node
             * @return * return true if loaded, false on error
             */
            bool load_from_xml(XMLNode* node);

            /**
             * @brief Get the Texture object
             * 
             * @return * return the texture of the island
             */
            SDL_Texture* getTexture(void){return this->texture;}

            /**
             * @brief Get the Rect object
             * 
             * @return SDL_Rect 
             */
            SDL_Rect getRect(void){return this->rect;}

            /**
             * @brief Get the pointer of the rect
             * 
             * @return * return the pointer of island's rect
             */
            SDL_Rect* getRect_ptr(void){return &this->rect;}

            /**
             * @brief Get the Name object
             * 
             * @return * return the name of the type 
             */
            string getName(void){return name;}
            

        private:
            /**
             * @brief the texture of the island
             * 
             */
            SDL_Texture* texture;

            /**
             * @brief the rectangle of the island
             * 
             */
            SDL_Rect rect;

            /**
             * @brief the name of the island type
             * 
             */
            string name;
    };

    class Island_type_list{
        public:
            /**
             * @brief Construct a new Island_type_list object
             * 
             */
            Island_type_list();

            /**
             * @brief Destroy the Island_type_list object
             * 
             */
            ~Island_type_list();

            /**
             * @brief search an island type from a name
             * 
             * @param name the search name
             * @return return the type if found, NULL otherwise
             */
            Island_type* search(string name);

            /**
             * @brief push a ne island in the vector
             * 
             * @param type the new type
             */
            void push(Island_type* type);
        
        private:
            /**
             * @brief the type of the island
             * 
             */
            vector<Island_type*> types;
    };

    class Island_list;

    class Island{
        public:
            /**
             * @brief Construct a new Island object
             * 
             */
            Island();

            /**
             * @brief Destroy the Island object
             * 
             */
            ~Island();

            /**
             * @brief load the island from an xml node
             * 
             * @param node the xml node
             * @return * return true if loaded, false on error
             */
            bool load_from_xml(XMLNode* node);

            /**
             * @brief Set the type of the island
             * 
             * @param name the name if the type
             * @return * return tre if loaded, false on error
             */
            bool set(string name);

            /**
             * @brief set the angle of the island
             * 
             * @param new_angle 
             */
            void setAngle(int new_angle){angle = new_angle;}

        private:
            Island_type* type;

            SDL_Rect rect;

            int angle;
    };

    class Island_list{
        public:
            /**
             * @brief Construct a new Island_list object
             * 
             */
            Island_list();

            /**
             * @brief Destroy the Island_list object
             * 
             */
            ~Island_list();

            /**
             * @brief get the island with the specified id
             * 
             * @param id the id
             * @return * return the island with the id, retrun nullptr on error
             */
            Island* get(int id);

            /**
             * @brief get teh id of the island
             * 
             * @param island the island
             * @return * return the id of the island, return -1 on error
             */
            int getID(Island* island);

            /**
             * @brief get the fisrt island of the islands vector
             * 
             * @return * return the first element of the islands vector 
             */
            Island* get();

            /**
             * @brief get if the inptu id is early used by an island
             * 
             * @param id the id
             * @return * return true if the id is early used, false otherwise
             */
            bool usedID(int id);

            /**
             * @brief Get the an unused id
             * 
             * @return * return an id who is not used by an island 
             */
            int get_unusedId(void);

            /**
             * @brief push if new island into the islands vector
             * 
             * @param island the new island
             */
            void push(Island* island);

        private:

            /**
             * @brief the id of the next pushed island
             * 
             */
            int id;

            /**
             * @brief child of an island class with an id int member
             * 
             */
            class Island_element : public Island{
                public:
                    Island_element();
                    ~Island_element();

                    /**
                     * @brief get the id of the island
                     * 
                     * @return * return the id
                     */
                    int getID(void){return id;}

                    /**
                     * @brief get the pointer of the island's id
                     * 
                     * @return * return the id's pointer 
                     */
                    int& getID_ptr(void){return id;}

                    /**
                     * @brief set the id
                     * 
                     * @param id the new id
                     */
                    void setID(int id){this->id = id;}
                private:
                    int id;
            };
            
            /**
             * @brief the vector of islands
             * 
             */
            vector<Island_list::Island_element*> islands;

    };

    Island_type_list& operator<<(Island_type_list& list, Island_type* type);
    bool operator==(Island_type* type, string name);
    Island_list& operator<<(Island_list& list, Island* type);

#endif