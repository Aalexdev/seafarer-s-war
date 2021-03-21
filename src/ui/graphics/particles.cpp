#include <cstdlib>
#include <SDL2/SDL2_gfxPrimitives.h>

#include "ui/graphics/particles.hpp"
#include "ui/graphics/light.hpp"
#include "main.hpp"

void pushParticle_type(XMLNode* node){
    Particles_type* type = new Particles_type();

    if (type->load(node)){
        PARTICLES_TYPE.push_back(type);
    } else {
        delete type;
    }
}

Particles_type::Particles_type(){
    light = NULL;
}

Particles_type::~Particles_type(){
    if (light) delete light;
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
            light = new Light;

            for (int a=0; a<child->attributes.size; a++){
                XMLAttribute attr = child->attributes.data[a];

                if (!strcmp(attr.key, "radius")){
                    sscanf(attr.value, "%d", &light->radius);
                } else if (!strcmp(attr.key, "r")){
                    sscanf(attr.value, "%d", &light->r);
                } else if (!strcmp(attr.key, "g")){
                    sscanf(attr.value, "%d", &light->g);
                } else if (!strcmp(attr.key, "b")){
                    sscanf(attr.value, "%d", &light->b);
                } else if (!strcmp(attr.key, "a")){
                    sscanf(attr.value, "%d", &light->a);
                } else {
                    if (IS_ERR_OPEN) ERR << "WARNING :: particles; light, reason : cannot reconize '" << attr.key << "' light attribute" << endl;
                }
            }
        } else {
            if (IS_ERR_OPEN) ERR << "WARNING :: particle, reason : cannot reconize : '" << child->tag << "' particle child" << endl;
        }
    }

    print();
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

    if (light){
        cout << "light :: radius : " << light->radius << ", r : " << light->r << ", g : " << light->g << ", b : " << light->b << ", a : " << light->a << endl; 
    } else {
        cout << " - no light effect -" << endl;
    }

    cout << endl;
}

Particles_type::Light* Particles_type::getLight(void){
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

// particles

Particles::Particles(){
    unlink();
}

Particles::~Particles(){
    unlink();
}

void Particles::unlink(void){
    type = nullptr;
    particles.clear();
    pos.x = 0;
    pos.y = 0;
}

bool Particles::set(string type_name){
    type = searchParticle(type_name);
    return type;
}

Particles_type* searchParticle(string name){
    for (Particles_type* t : PARTICLES_TYPE){
        if (t->getName() == name){
            return t;
        }
    }
    return nullptr;
}

void Particles::pushParticle(void){
    if (!type) return;

    Particle *p = new Particle;
    p->tick = SDL_GetTicks();
    p->vector.x = cosf(getRandAngle() * (M_PI / 180.0f)) * type->getStrength();
    p->vector.y = sinf(getRandAngle() * (M_PI / 180.0f)) * type->getStrength();

    p->pos.x = pos.x;
    p->pos.y = pos.y;

    p->r = getR();
    p->g = getG();
    p->b = getB();
    p->a = getA();

    int temp = (rand() % 2);

    if (temp == 1){
        p->sub = Particle::Particle_subX;
    } else {
        p->sub = Particle::Particle_subY;
    }
    
    particles.push_back(p);
}

void Particles::setPos(int x, int y){
    pos.x = x;
    pos.y = y;
}

int Particles::getZ(void){
    return z;
}

void Particles::setZ(int z){
    this->z = z;
}

bool Particles::drawLight(int z){
    if (!type) return false;
    if (!type->getLight()) return true;

    for (Particle* p : particles){
        light(type->getLight()->radius, p->pos.x, p->pos.y, type->getLight()->r, type->getLight()->g, type->getLight()->b);
    }

    return true;
}

bool Particles::draw(int z){
    if (!type) return false;
    if (this->z != z) return true;

    int tick = SDL_GetTicks();
    int i = 0;

    for (Particle* p : particles){
        if (p){
            if (tick - p->tick >= type->getTime()){
                particles.erase(particles.begin() + i);
                continue;
            }

            SDL_SetRenderDrawBlendMode(RENDERER, SDL_BLENDMODE_MOD);

            switch (type->getStyle()){
                
                case Particles_type::Particle_circle:
                    if (type->getStyleType()->circle.filled){
                        if (filledCircleRGBA(RENDERER, p->pos.x, p->pos.y, type->getStyleType()->circle.radius, p->r, p->g, p->b, p->a)){
                            if (IS_ERR_OPEN) ERR << "ERROR :: filledCircleRGBA, reason : " << SDL_GetError() << endl;
                            return false;
                        }
                    } else {
                        if (circleRGBA(RENDERER, p->pos.x, p->pos.y, type->getStyleType()->circle.radius, p->r, p->g, p->b, p->a)){
                            if (IS_ERR_OPEN) ERR << "ERROR :: circleRGBA, reason : " << SDL_GetError() << endl;
                            return false;
                        }
                    }
                    break;
                
                case Particles_type::Particle_ellipse:
                    if (type->getStyleType()->ellipse.filled){
                        if (filledEllipseRGBA(RENDERER, p->pos.x, p->pos.y, type->getStyleType()->ellipse.Vradius, type->getStyleType()->ellipse.Hradius, p->r, p->g, p->b, p->a)){
                            if (IS_ERR_OPEN) ERR << "ERROR :: filledEllipseRGBA, reason : " << SDL_GetError() << endl;
                            return false;
                        }
                    } else {
                        if (ellipseRGBA(RENDERER, p->pos.x, p->pos.y, type->getStyleType()->ellipse.Vradius, type->getStyleType()->ellipse.Hradius, p->r, p->g, p->b, p->a)){
                            if (IS_ERR_OPEN) ERR << "ERROR :: ellipseRGBA, reason : " << SDL_GetError() << endl;
                            return false;
                        }
                    }
                    break;
                
                case Particles_type::Particle_point:
                    SDL_SetRenderDrawColor(RENDERER, p->r, p->g, p->b, p->a);
                    if (SDL_RenderDrawPoint(RENDERER, p->pos.x, p->pos.y)){
                        if (IS_ERR_OPEN) ERR << "ERROR :: SDL_RenderDrawPoint, reason : " << SDL_GetError() << endl;
                        return false;
                    }
                    break;
                
                case Particles_type::Particle_square:
                    SDL_Rect rect;
                    
                    rect.x = p->pos.x - (type->getStyleType()->square.width / 2);
                    rect.y = p->pos.y - (type->getStyleType()->square.width / 2);
                    rect.w = type->getStyleType()->square.width;
                    rect.h = type->getStyleType()->square.width;

                    if (type->getStyleType()->square.filled){
                        if (SDL_RenderDrawRect(RENDERER, &rect)){
                            if (IS_ERR_OPEN) ERR << "ERROR :: SDL_RenderDrawRect, reason : " << SDL_GetError() << endl;
                        }
                    } else {
                        if (SDL_RenderFillRect(RENDERER, &rect)){
                            if (IS_ERR_OPEN) ERR << "ERROR :: SDL_RenderDrawRect, reason : " << SDL_GetError() << endl;
                        }
                    }
                    break;
                
                default:
                    break;
            }

            p->pos.x += p->vector.x * DELTA_TIME;
            p->pos.y += p->vector.y * DELTA_TIME;
        }

        i++;
    }

    pushParticles();

    return true;
}

int Particles::getRandAngle(void){
    return (rand() % range) + (angle + range/2);
}

int Particles::getR(void){
    int def = max(type->getEndColor().r, type->getStartColor().r) - min(type->getEndColor().r, type->getStartColor().r);
    if (def) return rand() % def + min(type->getEndColor().r, type->getStartColor().r);
    return 0;
}

int Particles::getG(void){
    int def = max(type->getEndColor().g, type->getStartColor().g) - min(type->getEndColor().g, type->getStartColor().g);
    if (def) return rand() % def + min(type->getEndColor().g, type->getStartColor().g);
    return 0;
}

int Particles::getB(void){
    int def = max(type->getEndColor().b, type->getStartColor().b) - min(type->getEndColor().b, type->getStartColor().b);
    if (def) return rand() % def + min(type->getEndColor().b, type->getStartColor().b);
    return 0;
}

int Particles::getA(void){
    int def = max(type->getEndColor().a, type->getStartColor().a) - min(type->getEndColor().a, type->getStartColor().a);
    if (def) return rand() % def + min(type->getEndColor().a, type->getStartColor().a);
    return 0;
}

void Particles::setRange(int range){
    this->range = range;
}

void Particles::setAngle(int angle){
    this->angle = angle;
}

void Particles::setDuration(int duration){
    if (duration != UNDEFINE) tick = SDL_GetTicks() + duration;
    else tick = UNDEFINE;
}

bool Particles::should_delete(void){
    if (tick != UNDEFINE) return (SDL_GetTicks() >= tick);
    return false;
}

void Particles::pushParticles(void){
    for (int i=0; i<type->getDensity(); i++){
        pushParticle();
    }
}