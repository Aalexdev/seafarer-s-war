#include "ui/graphics/effect_type.hpp"
#include "main.hpp"


Particles_type::Particles_type(){
    light.clear();
}

Particles_type::~Particles_type(){
    light.clear();
}

bool Particles_type::load(XMLNode* node){
    if (!node){
        if (IS_ERR_OPEN) ERR << "ERROR :: Particles_type::load, reason : cannot load from a null node" << endl;
        return false;
    }

    for (int a=0; a<node->attributes.size; a++){
        XMLAttribute attr = node->attributes.data[a];

        if (!strcmp(attr.key, "name")){
            name = attr.value;
        } else if (!strcmp(attr.key, "strength")){
            sscanf(attr.value, "%f", &particule_strength);
        } else if (!strcmp(attr.key, "density")){
            sscanf(attr.value, "%d", &density);
        } else if (!strcmp(attr.key, "time")){
            sscanf(attr.value, "%d", &point_time);
        } else {
            if (IS_ERR_OPEN) ERR << "WARNING :: particle, reason : cannot reconize '" << attr.key << "' particle attribute" << endl;
        }
    }

    for (int c=0; c<node->children.size; c++){
        XMLNode* child = XMLNode_child(node, c);

        if (!strcmp(child->tag, "color")){
            for (int col=0; col<child->children.size; col++){
                XMLNode* color = XMLNode_child(child, col);

                if (!strcmp(color->tag, "start")){
                    for (int a=0; a<color->attributes.size; a++){
                        XMLAttribute attr = color->attributes.data[a];

                        if (!strcmp(attr.key, "r")){
                            sscanf(attr.value, "%d", &this->color.sColor.r);
                        } else if (!strcmp(attr.key, "g")){
                            sscanf(attr.value, "%d", &this->color.sColor.g);
                        } else if (!strcmp(attr.key, "b")){
                            sscanf(attr.value, "%d", &this->color.sColor.b);
                        } else if (!strcmp(attr.key, "a")){
                            sscanf(attr.value, "%d", &this->color.sColor.a);
                        } else {
                            if (IS_ERR_OPEN) ERR << "WARNING :: particle; color; start, reason : cannot reconize '" << attr.key << "' start attribute" << endl;
                        }
                    }
                } else if (!strcmp(color->tag, "end")){
                    for (int a=0; a<color->attributes.size; a++){
                        XMLAttribute attr = color->attributes.data[a];

                        if (!strcmp(attr.key, "r")){
                            sscanf(attr.value, "%d", &this->color.eColor.r);
                        } else if (!strcmp(attr.key, "g")){
                            sscanf(attr.value, "%d", &this->color.eColor.g);
                        } else if (!strcmp(attr.key, "b")){
                            sscanf(attr.value, "%d", &this->color.eColor.b);
                        } else if (!strcmp(attr.key, "a")){
                            sscanf(attr.value, "%d", &this->color.eColor.a);
                        } else {
                            if (IS_ERR_OPEN) ERR << "WARNING :: particle; color; and, reason : cannot reconize '" << attr.key << "' end attribute " << endl;
                        }
                    }
                } else {
                    if (IS_ERR_OPEN) ERR << "WARNING :: particle; color, reason : cannot reconize '" << color->tag << "' color children" << endl;
                }
            }
        } else if (!strcmp(child->tag, "circle")){
            setCircle();
            for (int a=0; a<child->attributes.size; a++){
                XMLAttribute attr = child->attributes.data[a];
                
                if (!strcmp(attr.key, "radius")){
                    sscanf(attr.value, "%d", &style.circle.radius);
                } else if (!strcmp(attr.key, "filled")){
                    string value = attr.value;
                    if (value == "true"){
                        style.circle.filled = true;
                    } 
                } else {
                    if (IS_ERR_OPEN) ERR << "WARNING :: particle; circle, reason : cannot reconize '" << attr.key << "' circle attribute" << endl;
                }
            }
        } else if (!strcmp(child->tag, "square")){
            setSquare();
            for (int a=0; a<child->attributes.size; a++){
                XMLAttribute attr = child->attributes.data[a];
                
                if (!strcmp(attr.key, "width")){
                    sscanf(attr.value, "%d", &style.square.width);
                } else if (!strcmp(attr.key, "filled")){
                    string value = attr.value;
                    if (value == "true"){
                        style.square.filled = true;
                    } 
                } else {
                    if (IS_ERR_OPEN) ERR << "WARNING :: particle; square, reason : cannot reconize '" << attr.key << "' square attribute" << endl;
                }
            }
        } else if (!strcmp(child->tag, "ellipse")){
            setEllipse();
            for (int a=0; a<child->attributes.size; a++){
                XMLAttribute attr = child->attributes.data[a];
                
                if (!strcmp(attr.key, "vertical-radius")){
                    sscanf(attr.value, "%d", &style.ellipse.Vradius);
                } else if (!strcmp(attr.key, "horisontal-radius")){
                    sscanf(attr.value, "%d", &style.ellipse.Hradius);
                } else if (!strcmp(attr.key, "filled")){
                    string value = attr.value;
                    if (value == "true"){
                        style.ellipse.filled = true;
                    } 
                } else {
                    if (IS_ERR_OPEN) ERR << "WARNING :: particle; ellipse, reason : cannot reconize '" << attr.key << "' ellipse attribute" << endl;
                }
            }
        } else if (!strcmp(child->tag, "point/")){
            setPoint();
        } else if (!strcmp(child->tag, "light")){
            for (int a=0; a<child->attributes.size; a++){
                XMLAttribute attr = child->attributes.data[a];

                if (!strcmp(attr.key, "type")){
                    light = attr.value;
                } else {
                    if (IS_ERR_OPEN) ERR << "WARNING :: particles; light, reason : cannot reconize '" << attr.key << "' light attribute" << endl;
                }
            }
        } else {
            if (IS_ERR_OPEN) ERR << "WARNING :: particle, reason : cannot reconize : '" << child->tag << "' particle child" << endl;
        }
    }

    if (IS_DEBUG) print();
    return true;
}

void Particles_type::setColor(SDL_Color sColor, SDL_Color eColor){
    color.eColor = eColor;
    color.sColor = sColor;
}

void Particles_type::setEndingColor(SDL_Color color){
    this->color.eColor = color;
}

void Particles_type::setStartingColor(SDL_Color color){
    this->color.sColor = color;
}

void Particles_type::setTime(int time){
    point_time = time;
}

void Particles_type::setStrength(float strength){
    particule_strength = strength;
}

// particles private --- --- ---

void Particles_type::setCircle(void){
    style_type = Particle_circle;
    style.circle.radius = 5;
    style.circle.filled = false;
}

void Particles_type::setPoint(void){
    style_type = Particle_point;
}

void Particles_type::setSquare(void){
    style_type = Particle_square;
    style.square.width = 5;
    style.square.filled = false;
}

void Particles_type::setEllipse(void){
    style_type = Particle_ellipse;
    style.ellipse.filled = false;
    style.ellipse.Hradius = 5;
    style.ellipse.Vradius = 5;
}

void Particles_type::print(void){
    cout << endl;
    cout << "particles type : " << name << endl;
    cout << "------------------------------" << endl;
    cout << "starting color : " << (int)color.sColor.r << ", " << (int)color.sColor.g << ", " << (int)color.sColor.b << ", " << (int)color.sColor.a << endl;
    cout << "ending color : " << (int)color.eColor.r << ", " << (int)color.eColor.g << ", " << (int)color.eColor.b << ", " << (int)color.eColor.a << endl;

    cout << "type : ";

    switch (style_type){
        case Particle_circle:
            cout << "circle" << endl;
            cout << "radius : " << style.circle.radius << ", filled : " << style.circle.filled << endl;
            break;
        
        case Particle_ellipse:
            cout << "ellipse" << endl;
            cout << "vertical-radius : " << style.ellipse.Vradius << ", horisontal-radius : " << style.ellipse.Hradius << ", filled : " << style.ellipse.filled << endl;
            break;
        
        case Particle_point:
            cout << "point" << endl;
            break;
        
        case Particle_square:
            cout << "square" << endl;
            cout << "width : " << style.square.width << ", filled : " << style.square.filled << endl;
            break;

        default:
            break;
    }

    cout << ", strength : " << particule_strength << endl;

    if (!light.empty()){
        cout << "light :: radius : " << light << endl; 
    } else {
        cout << " - no light effect -" << endl;
    }

    cout << endl;
}

string Particles_type::getLight(void){
    return light;
}

string Particles_type::getName(void){
    return name;
}

float Particles_type::getStrength(void){
    return particule_strength;
}

int Particles_type::getTime(void){
    return point_time;
}

Particles_type::Particle_Style Particles_type::getStyle(void){
    return style_type;
}

Particles_type::Particle_style* Particles_type::getStyleType(void){
    return &style;
}

SDL_Color Particles_type::getStartColor(void){
    return color.sColor;
}

SDL_Color Particles_type::getEndColor(void){
    return color.eColor;
}

int Particles_type::getDensity(void){
    return density;
}

void pushParticle_type(XMLNode* node){
    Particles_type* type = new Particles_type();

    if (type->load(node)){
        PARTICLES_TYPE.push_back(type);
    } else {
        delete type;
    }
}

bool operator==(Particles_type* type, string name){
    if (!type) return false;
    return type->getName() == name;
}

Particles_type* searchParticle(string name){
    for (Particles_type* t : PARTICLES_TYPE){
        if (t == name){
            return t;
        }
    }
    return nullptr;
}

void clear_particlesType(void){
    for (Particles_type* t : PARTICLES_TYPE){
        delete t;
    }
    PARTICLES_TYPE.clear();
}