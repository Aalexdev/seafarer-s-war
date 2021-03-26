#ifndef __EFFECT_TYPE__
#define __EFFECT_TYPE__

    #include "api/io/xml.hpp"

    class Effect_type{
        public:
            /**
             * @brief Construct a new Effect_type object
             * 
             */
            Effect_type();

            /**
             * @brief Destroy the Effect_type object
             * 
             */
            ~Effect_type();

            /**
             * @brief load the type from a xml node
             * 
             * @param node the xml node
             * @return return true if loaded, false on error
             */
            bool load(XMLNode* node);



        private:
            /**
             * @brief the name if the type
             * 
             */
            string _name;

            
    };

#endif