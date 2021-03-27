#include "ui/graphics/particles_type.hpp"
#include "main.hpp"

Particles_type::Particles_type(){
    if (IS_LOG_OPEN) LOG << "Particles_type::Particles_type()" << endl;

}

Particles_type::~Particles_type(){
    if (IS_LOG_OPEN) LOG << "Particles_type::~Particles_type()" << endl;

}

bool Particles_type::load(XMLNode* node){
    if (IS_LOG_OPEN) LOG << "Particles_type::load()" << endl;
    if (!node){
        if (IS_ERR_OPEN) ERR << "ERROR :: Particles_type::load, reason : cannot load a particles type without a xml node" << endl;
        return false;
    }

    /*
    <particle-type name="_name">
        
        <colors>
            <color r="r" g="g" b="b" a="a"/>
        </colors>
     
    </particle-type>
    */
   
    // attributes
    for (int a=0; a<node->attributes.size; a++){
        XMLAttribute attr = node->attributes.data[a];

        if (!strcmp(attr.key, "name")){
            _name = attr.value;
        } else {
            if (IS_ERR_OPEN) ERR << "WARNING :: particle-type, reason : cannot reconize '" << attr.key << "' particles-type attribute" << endl;
        }
    }

    // child
    for (int c=0; c<node->children.size; c++){
        XMLNode* child = XMLNode_child(node, c);

        if (!strcmp(child->tag, "colors")){
            for (int col=0; col<child->children.size; col++){
                XMLNode* col_node = XMLNode_child(child, col);

                if (!strcmp(col_node->tag, "color")){
                    pushColor(col_node);
                } else {
                    if (IS_ERR_OPEN) ERR << "WARNING :: particle-type; colors, reason : cannot reconize '" << col_node->tag << "' colors children" << endl;
                }
            }
        }
    }

    return true;
}

string Particles_type::name(void){
    return _name;
}

void Particles_type::name(string name){
    _name = name;
}

void Particles_type::pushColor(XMLNode* color_node){
    SDL_Color* color = new SDL_Color;

    color->r = 0;
    color->g = 0;
    color->b = 0;
    color->a = 0;

    for (int a=0; a<color_node->attributes.size; a++){
        XMLAttribute attr = color_node->attributes.data[a];

        if (!strcmp(attr.key, "r")){
            sscanf(attr.value, "%d", &color->r);
        } else if (!strcmp(attr.key, "g")){
            sscanf(attr.value, "%d", &color->g);
        } else if (!strcmp(attr.key, "b")){
            sscanf(attr.value, "%d", &color->b);
        } else if (!strcmp(attr.key, "a")){
            sscanf(attr.value, "%d", &color->a);
        } else {
            if (IS_ERR_OPEN) ERR << "WARNING :: particle-type; colors; color, reason : cannot reconize '" << attr.key << "' color attribute" << endl;
        }
    }

    _colors.push_back(color);
}

vector<SDL_Color*> Particles_type::colors(void){
    return _colors;
}

SDL_Color Particles_type::get_random_color(void){
    if (!_colors.empty()){
        SDL_Color* temp = _colors[(rand() % _colors.size())];
        return {temp->r, temp->g, temp->b, temp->a};
    }
    return {0, 0, 0, 0};
}

Particles_type* search_particle_type(string name){
    for (Particles_type* t : PARTICLES_TYPE){
        if (t == name){
            return t;
        }
    }
    return nullptr;
}

void push_particle_type(XMLNode* node){
    Particles_type* t = new Particles_type();

    if (t->load(node)){
        PARTICLES_TYPE.push_back(t);
    } else {
        delete t;
    }
}

bool operator==(Particles_type* t, string name){
    if (!t) return false;
    return t->name() == name;
}

void clear_particles_type(void){
    for (Particles_type* t : PARTICLES_TYPE){
        delete t;
    }
    PARTICLES_TYPE.clear();
}