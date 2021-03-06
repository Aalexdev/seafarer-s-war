#include "api/class/entity.hpp"
#include "main.hpp"
#include "api/functions/math.hpp"

#include "SDL2/SDL2_gfxPrimitives.h"

Point* getPoint(Entity* e){
    Point *p;
    e->getPart(&p);
    return p;
}

Point* convertPartsIntoPoints(Entity_point* p, int n){
    Point *pts = new Point[n];

    for (int i=0; i<n; i++){
       pts[i].x = p[i].x;
       pts[i].y = p[i].y; 
    }

    return pts;
}

Entity_type::Entity_type(){
    if (IS_LOG_OPEN) LOG << "Entity_type::Entity_type()" << endl;
    this->name = "Uncknow";
    this->rect = (SDL_Rect){0, 0, 0, 0};
    this->mass = 0;
    onDeath = NULL;
}

Entity_type::~Entity_type(){
    if (IS_LOG_OPEN) LOG << "Entity_type::~Entity_type()" << endl;
    if (this->texture) SDL_DestroyTexture(this->texture);
    this->name.clear();

    delete[] part;
    delete[] equipments;

    if (onDeath) delete onDeath;
}

bool Entity_type::load_from_xml(XMLNode* node){

    if (IS_LOG_OPEN) LOG << "Entity_type::load_from_xml" << endl;
    if (!node){
        if (IS_ERR_OPEN) ERR << "ERROR :: Entity_load::load_from_xml, reason : cannot load from a null node" << endl;
        return false;
    }

    for (int a=0; a<node->attributes.size; a++){
        XMLAttribute attr = node->attributes.data[a];

        if (!strcmp(attr.key, "name")){

            if (!this->used_name(attr.value)){
                this->name = attr.value;
            } else {
                if (IS_ERR_OPEN) ERR << "ERROR :: Entity_type::load_from_xml, reason : name '" << attr.value << "' is erealy used" << endl;
                return false;
            }

        } else {
            if (IS_ERR_OPEN) ERR << "WARNING :: Entity_type::load_from_xml, reason : cannot reconize '" << attr.key << "' entity attribute" << endl;
        }
    }

    for (int c=0; c<node->children.size; c++){
        XMLNode* child = XMLNode_child(node, c);

        if (!strcmp(child->tag, "texture")){
            for (int a=0; a<child->attributes.size; a++){
                XMLAttribute attr = child->attributes.data[a];

                if (!strcmp(attr.key, "path")){
                    int w=this->rect.w, h=this->rect.h;
                    this->texture = loadTexture(attr.value, &this->rect);
                    SDL_SetTextureBlendMode(texture, SDL_BLENDMODE_MUL);
                } else if (!strcmp(attr.key, "w")){
                    sscanf(attr.value, "%d", &this->rect.w);
                } else if (!strcmp(attr.key, "h")){
                    sscanf(attr.value, "%d", &this->rect.h);
                } else {
                    if (IS_ERR_OPEN) ERR << "WARNING :: Entity_type::load_from_xml, reason : cannot reconize '" << attr.key << "' texture attribute" << endl;
                }
            }
        } else if (!strcmp(child->tag, "perform")){
            for (int a=0; a<child->attributes.size; a++){
                XMLAttribute attr = child->attributes.data[a];

                if (!strcmp(attr.key, "mass")){
                    sscanf(attr.value, "%f", &this->mass);
                } else if (!strcmp(attr.key, "strength")){
                    sscanf(attr.value, "%f", &this->strength);
                } else if (!strcmp(attr.key, "maxSpeed")){
                    sscanf(attr.value, "%d", &this->maxSpeed);
                } else if (!strcmp(attr.key, "minSpeed")){
                    sscanf(attr.value, "%d", &this->minSpeed);
                } else {
                    if (IS_ERR_OPEN) ERR << "ERROR :: Entity_type;;load_from_xml, reason : cannot reconize '" << attr.key << "' perform attribute" << endl;
                }
            }
        } else if (!strcmp(child->tag, "layer")){
            for (int a=0; a<child->attributes.size; a++){
                XMLAttribute attr = child->attributes.data[a];

                if (!strcmp(attr.key, "max")){
                    sscanf(attr.value, "%d", &this->layerMax);
                } else if (!strcmp(attr.key, "min")){
                    sscanf(attr.value, "%d", &this->layerMin);
                } else {
                    if (IS_ERR_OPEN) ERR << "WARNING :: Entity_type::load_from_xml, reason : cannot reconize '" << attr.key << "' layer attribute" << endl;
                }
            }
        } else if (!strcmp(child->tag, "turn")){
            for (int a=0; a<child->attributes.size; a++){
                XMLAttribute attr = child->attributes.data[a];

                if (!strcmp(attr.key, "type")){
                    string type = attr.value;

                    if (type == "free"){
                        turnType = TurnType::Turnfree;
                    } else if (type == "mul"){
                        turnType = TurnType::Turnmul;
                    } else if (type == "div"){
                        turnType = TurnType::Turndiv;
                    } else if (type == "add"){
                        turnType = TurnType::Turnadd;
                    } else if (type == "sub"){
                        turnType = TurnType::Turnsub;
                    }
                } else if (!strcmp(attr.key, "value")){
                    if (turnType == TurnType::Turnfree){
                        if (IS_ERR_OPEN) ERR << "WARNING :: Entity_type::load_from_xml, reason : cannot set a value to a null trun type, ignored" << endl;
                        break;
                    }

                    sscanf(attr.value, "%d", &turnValue);

                    if (turnType == TurnType::Turndiv && turnValue == 0){
                        if (IS_ERR_OPEN) ERR << "WARNING :: Entity_type::load_from_xml, reason : cannot divid the rotaionnal speed with a nul value, set value to 1" << endl;
                        turnValue = 1;
                    }
                } else if (!strcmp(attr.key, "max")){
                    sscanf(attr.value, "%f", &maxRotarySpeed);
                } else {
                    if (IS_ERR_OPEN) ERR << "WARNING :: Entity_type::load_from_xml, reason : cannot reconize '" << attr.key << "' entity trun attribute" << endl;
                }
            }
        } else if (!strcmp(child->tag, "part")){

            for (int a=0; a<child->attributes.size; a++){
                XMLAttribute attr = child->attributes.data[a];

                if (!strcmp(attr.key, "health")){
                    sscanf(attr.value, "%d", &health);
                }
            }

            partSize = child->children.size;
            part = new Entity_point[child->children.size];

            for (int p=0; p<child->children.size; p++){
                XMLNode* point = XMLNode_child(child, p);

                if (!strcmp(point->tag, "point")){
                    int x, y;
                    for (int a=0; a<point->attributes.size; a++){
                        XMLAttribute attr = point->attributes.data[a];

                        if (!strcmp(attr.key, "x")){
                            sscanf(attr.value, "%d", &part[p].x);
                        } else if (!strcmp(attr.key, "y")){
                            sscanf(attr.value, "%d", &part[p].y);
                        } else {
                            if (IS_ERR_OPEN) ERR << "WARNING :: entity, part, point, reason : cannot reconize '" << attr.key << "' point attribute" << endl;
                        }
                    }
                    part[p].distFromCenter = getDistanceM(rect.w / 2, rect.h / 2, part[p].x, part[p].y);
                    part[p].additionnalAngle = getAngleM(part[p].x, part[p].y, rect.w / 2, rect.h / 2);
                } else {
                    if (IS_ERR_OPEN) ERR << "WARNING :: entity, part, cannot reconize '" << point->tag << "' part child" << endl;
                }
            }
        } else if (!strcmp(child->tag, "equipments")){

            equipments_len = child->children.size;
            equipments = new Entity_Equipment[equipments_len];

            for (int e=0; e<child->children.size; e++){
                XMLNode* equip = XMLNode_child(child, e);

                if (!strcmp(equip->tag, "equipment")){

                    for (int a=0; a<equip->attributes.size; a++){
                        XMLAttribute attr = equip->attributes.data[a];

                        if (!strcmp(attr.key, "x")){
                            sscanf(attr.value, "%d", &equipments[e].x);
                        } else if (!strcmp(attr.key, "y")){
                            sscanf(attr.value, "%d", &equipments[e].y);
                        } else if (!strcmp(attr.key, "min-angle")){
                            sscanf(attr.value, "%d", &equipments[e].minAngle);
                        } else if (!strcmp(attr.key, "max-angle")){
                            sscanf(attr.value, "%d", &equipments[e].maxAngle);
                        } else if (!strcmp(attr.key, "id")){
                            sscanf(attr.value, "%d", &equipments[e].id);
                        } else {
                            if (IS_ERR_OPEN) ERR << "WARNING :: entity; equipments; equipment, reason : cannot reconize '" << attr.key << "' equipment attribute" << endl;
                        }
                    }
                } else {
                    if (IS_ERR_OPEN) ERR << "WARNING :: entity; equipments, reason : cannot reconize '" << equip->tag << " equipments child" << endl;
                }

                equipments[e].distFromCenter = getDistanceM(rect.w / 2, rect.h / 2, equipments[e].x, equipments[e].y);
                equipments[e].additionnalAngle = getAngleM(equipments[e].x, equipments[e].y, rect.w / 2, rect.h / 2);
            }
        } else if (!strcmp(child->tag, "OnDeath")){
            onDeath = new OnDeath;

            for (int a=0; a<child->attributes.size; a++){
                XMLAttribute attr = child->attributes.data[a];

                if (!strcmp(attr.key, "layer")){
                    sscanf(attr.value, "%d", &onDeath->z);
                } else if (!strcmp(attr.key, "time")){
                    sscanf(attr.value, "%d", &onDeath->time);
                } else {
                    if (IS_ERR_OPEN) ERR << "WARNING :: entity; OnDeath, reason : cannot rconize '" << attr.key << "' onDeath child" << endl;
                }
            }
        } else {
            if (IS_LOG_OPEN) ERR << "WARNING :: entity, reason : cannot reconize '" << child->tag << "' entity child" << endl;
        }
    }
    return true;
}

int Entity_type::getPartSize(void){
    return partSize;
}

Entity_point* Entity_type::getPart(void){
    return part;
}

Entity_Equipment* Entity_type::getEquipment(void){
    return equipments;
}

int Entity_type::getEquipmentSize(void){
    return equipments_len;
}

Entity_type::OnDeath* Entity_type::getDeath(void){
    return onDeath;
}

bool Entity::set(string name){
    if (IS_LOG_OPEN) LOG << "Entity::set('" << name << "')" << endl;
    if (name.empty()){
        if (IS_ERR_OPEN) ERR << "ERROR :: Entity::set, reason : cannot load a null type name" << endl;
        return false;
    }

    for (Entity_type* type : ENTITY_TYPES){
        if (type->get_name() == name){
            this->type = type;

            this->rect.w = type->getRect().w;
            this->rect.h = type->getRect().h;

            part = new Entity_point[type->getPartSize()];

            for (int i=0; i<type->getPartSize(); i++){
                part[i].x = type->getPart()[i].x;
                part[i].y = type->getPart()[i].y;
                part[i].distFromCenter = type->getPart()[i].distFromCenter;
                part[i].additionnalAngle = type->getPart()[i].additionnalAngle;
            }

            equipmentsP = new Entity_point[type->getEquipmentSize()];

            for (int i=0; i<type->getEquipmentSize(); i++){
                equipmentsP[i].x = type->getEquipment()[i].x;
                equipmentsP[i].y = type->getEquipment()[i].y;
                equipmentsP[i].distFromCenter = type->getEquipment()[i].distFromCenter;
                equipmentsP[i].additionnalAngle = type->getEquipment()[i].additionnalAngle;
            }

            equipments = new Equipment*[type->getEquipmentSize()];

            for (int i=0; i<type->getEquipmentSize(); i++){
                equipments[i] = NULL;
            }

            if (IS_ERR_OPEN) LOG << "Entity::set() : type found '" << name << "'" << endl;
            return true;
        }
    }

    if (IS_ERR_OPEN) ERR << "ERROR :: Entity::set, reason : cannot load '" << name << "' entity name" << endl;
    return false;
}

bool Entity_type::used_name(string name){
    for (Entity_type* type : ENTITY_TYPES){
        if (type->get_name() == name){
            return true;
        }
    }
    return false;
}

bool Entity::load_from_xml(XMLNode* node){

    if (IS_LOG_OPEN) LOG << "Entity::load_from_xml()" << endl;
    if (!node){
        if (IS_ERR_OPEN) ERR << "ERROR :: Entity::load_from_xml, reason : cannot load from a null node" << endl;
        return false;
    }

    for (int a=0; a<node->attributes.size; a++){
        XMLAttribute attr = node->attributes.data[a];

        if (!strcmp(attr.key, "x")){
            sscanf(attr.value, "%d", &this->rect.x);
        } else if (!strcmp(attr.key, "y")){
            sscanf(attr.value, "%d", &this->rect.y);
        } else if (!strcmp(attr.key, "type")){
            if (!this->set(attr.value)) return false;
        } else if (!strcmp(attr.key, "height")){
            sscanf(attr.value, "%d", &this->z);
        } else if (!strcmp(attr.key, "angle")){
            sscanf(attr.value, "%f", &this->angle);
        } else {
            if (IS_ERR_OPEN) ERR << "WARNING :: Entity::load_from_xml, reason : cannot reconize '" << attr.key  << "' summonEntity attribute" << endl;
        }
    }


    for (int c=0; c<node->children.size; c++){
        XMLNode* child = XMLNode_child(node, c);

        if (!strcmp(child->tag, "team")){
            for (int a=0; a<child->attributes.size; a++){
                XMLAttribute attr = child->attributes.data[a];

                if (!strcmp(attr.key, "team")){
                    
                } else {
                    if (IS_ERR_OPEN) ERR << "WARNING :: Entity::load_from_xml, reason : cannot reconize '" << attr.key << "' team attribute" << endl;
                }
            }
        } else if (!strcmp(child->tag, "events")){
            if (!this->is_player) {
                if (IS_ERR_OPEN) ERR << "ERROR :: Entity::load_from_xml, reason : cannot set events of a not player entity" << endl;
            } else {
                for (int e=0; e<child->children.size; e++){
                    XMLNode* event_type = XMLNode_child(child, e);

                    if (!strcmp(event_type->tag, "keypad")){
                        for (int k=0; k<event_type->children.size; k++){
                            XMLNode* key = XMLNode_child(event_type, k);

                            if (!strcmp(key->tag, "key")){

                                string tag, out;
                                bool type = true;
                                for (int a=0; a<key->attributes.size; a++){
                                    XMLAttribute attr = key->attributes.data[a];

                                    if (!strcmp(attr.key, "tag")){
                                        tag = attr.value;
                                    } else if (!strcmp(attr.key, "out")){
                                        out = attr.value;
                                    } else if (!strcmp(attr.key, "type")){
                                        if (!strcmp(attr.value, "sticky")){
                                            type = false;
                                        } else if(!strcmp(attr.value, "push")){
                                            type = true;
                                        } else {
                                            if (IS_ERR_OPEN) ERR << "WARNING :: Entity::load_from_xml, reason : cannot reconize '" << attr.value << "' type value" << endl;
                                        }
                                    } else {
                                        if (IS_ERR_OPEN) ERR << "WARNING :: Entity::load_from_xml, reason : cannot reconize '" << attr.key << "' key attribute" << endl;
                                    }
                                }

                                if (!tag.empty() && !out.empty()){
                                    if (out == "engineUp"){
                                        PLAYER_CONTROL.engineUp = SDL_GetScancodeFromName(tag.c_str());
                                        PLAYER_CONTROL.engineUP_type = type;
                                    } else if (out == "engineDown"){
                                        PLAYER_CONTROL.engineDown = SDL_GetScancodeFromName(tag.c_str());
                                        PLAYER_CONTROL.engineDown_type = type;
                                    } else if (out == "turnLeft"){
                                        PLAYER_CONTROL.turnLeft = SDL_GetScancodeFromName(tag.c_str());
                                        PLAYER_CONTROL.turnLeft_type = type;
                                    } else if (out == "turnRight"){
                                        PLAYER_CONTROL.turnRight = SDL_GetScancodeFromName(tag.c_str());
                                        PLAYER_CONTROL.turnRight_type = type;
                                    } else if (out == "layerUp"){
                                        PLAYER_CONTROL.layerUp = SDL_GetScancodeFromName(tag.c_str());
                                        PLAYER_CONTROL.layerUp_type = type;
                                    } else if (out == "layerDown"){
                                        PLAYER_CONTROL.layerDown = SDL_GetScancodeFromName(tag.c_str());
                                        PLAYER_CONTROL.layerDown_type = type;
                                    } else if (out == "lights"){
                                        PLAYER_CONTROL.lights = SDL_GetScancodeFromName(tag.c_str());
                                        PLAYER_CONTROL.light_type = type;
                                    } else {
                                        if (IS_ERR_OPEN) ERR << "ERROR :: Entity::load_from_xml, reason : cannot reconize '" << out << "' key out" << endl;
                                    }
                                } else {
                                    if (IS_ERR_OPEN) ERR << "ERROR :: Entity::load_from_xml, reason : cannot load a key from an incomplet key node" << endl;
                                }
                            } else {
                                if (IS_ERR_OPEN) ERR << "WARNING :: Entity::load_from_xml, reason : cannot reconize '" << key->tag << "' keypad child" << endl;
                            }
                        }
                    } else if (!strcmp(event_type->tag, "mouse")){

                    } else {
                        if (IS_ERR_OPEN) ERR << "WARNING :: Entity::load_from_xml, reason : cannot reconize '" << event_type->tag << "' events child" << endl;
                    }
                }
            }
            
        } else if (!strcmp(child->tag, "part")){

            for (int a=0; a<child->attributes.size; a++){
                XMLAttribute attr = child->attributes.data[a];

                if (!strcmp(attr.key, "health")){
                    sscanf(attr.value, "%d", &health);
                } else {
                    if (IS_ERR_OPEN) ERR << "WARNING :: summonEntity; parts; part, reason : cannot reconize '" << attr.key << "' part attribute" << endl;
                }
            }
            if (child->children.size > 0){
                if (IS_ERR_OPEN) ERR << "WARNING :: summonEnity; part, reason : part cannot have child (" << child->children.size << ">0)" << endl; 
            }
        } else if (!strcmp(child->tag, "equipments")){
            for (int e=0; e<child->children.size; e++){
                XMLNode* node = XMLNode_child(child, e);

                if (e < type->getEquipmentSize()){
                    if (!strcmp(node->tag, "equipment")){
                        equipments[e] = new Equipment(this);

                        if (!equipments[e]){
                            if (IS_ERR_OPEN) ERR << "ERROR :: ALLOC error" << endl;
                            return false;
                        }

                        for (int a=0; a<node->attributes.size; a++){
                            XMLAttribute attr = node->attributes.data[a];

                            if (!strcmp(attr.key, "name")){
                                if (!equipments[e]->setType(attr.value)){
                                    delete equipments[e];
                                    equipments[e] = nullptr;
                                    break;
                                }
                            } else if (!strcmp(attr.key, "id")){
                                sscanf(attr.value, "%d", &equipments[e]->id);
                            } else if (!strcmp(attr.key, "angle")){
                                int angle;
                                sscanf(attr.value, "%d", &angle);
                                equipments[e]->setAngle(angle);
                            } else {
                                if (IS_ERR_OPEN) ERR << "ERROR :: summonEntity; equipments; equipment, reason : cannot reconize '" << attr.key << "' equipment attribute" << endl; 
                            }
                        }
                    } else {
                        equipments[e] = NULL;
                        if (IS_ERR_OPEN) ERR << "WARNIGN :: summonEntity; equipments, reason : cannot reconize '" << node->tag << "' equipments child" << endl;
                    }
                } else {
                    if (IS_ERR_OPEN) ERR << "WARNIGN :: summonEntity; equipments, reason : cannot set more equipment than the type has (" << e << ">" << type->getEquipmentSize() << endl;
                }
            }
        } else if (!strcmp(child->tag, "particles")){
            for (int p=0; p<child->children.size; p++){
                XMLNode* particles_node = XMLNode_child(child, p);

                if (!strcmp(particles_node->tag, "particle")){
                    Particles* particles = create_particle();
                    objectAttribute* oa = new objectAttribute;

                    SDL_Point p = {0, 0};

                    for (int a=0; a<particles_node->attributes.size; a++){
                        XMLAttribute attr = particles_node->attributes.data[a];

                        if (!strcmp(attr.key, "type")){
                            if (!particles->type(attr.value)){
                                delete particles;
                                delete oa;
                                particles = nullptr;
                                break;
                            }
                        } else if (!strcmp(attr.key, "angle")){
                            int angle;
                            sscanf(attr.value, "%d", &angle);
                            particles->angle(angle);
                            oa->objectAngle = angle;
                        } else if (!strcmp(attr.key, "range")){
                            int range;
                            sscanf(attr.value, "%d", &range);
                            particles->range(range);
                        } else if (!strcmp(attr.key, "x")){
                            sscanf(attr.value, "%d", &p.x);
                        } else if (!strcmp(attr.key, "y")){
                            sscanf(attr.value, "%d", &p.y);
                        } else {
                            if (IS_ERR_OPEN) ERR << "WARNING :: summonEntity; particles; particle, reason : cannot reconize '" << attr.key << "' particle attribute" << endl;
                        }
                    }

                    if (particles){
                        oa->angle = getAngleM(rect.w / 2, rect.h / 2, p.x, p.y) - 90;
                        oa->dist = getDistanceM(p.x, p.y, rect.w / 2, rect.h / 2);

                        this->particles.push_back(particles);
                        particles_point.push_back(oa);

                        particles->pushing(true);
                        particles->duration(PARTICLES_DURATION_UNLIMITED);
                    }

                } else {
                    if (IS_ERR_OPEN) ERR << "WARNING :: summonEntity; particles, reason : cannot reconize '" << particles_node->tag << "' particles child" << endl;
                }
            }
        } else if (!strcmp(child->tag, "lights")){
            for (int p=0; p<child->children.size; p++){
                XMLNode* light_node = XMLNode_child(child, p);

                if (!strcmp(light_node->tag, "light")){
                    Light* light = new Light();
                    objectAttribute* oa = new objectAttribute;

                    SDL_Point p = {0, 0};

                    for (int a=0; a<light_node->attributes.size; a++){
                        XMLAttribute attr = light_node->attributes.data[a];

                        if (!strcmp(attr.key, "type")){
                            if (!light->set(attr.value)){
                                delete light;
                                delete oa;
                                light = nullptr;
                                break;
                            }
                        } else if (!strcmp(attr.key, "x")){
                            sscanf(attr.value, "%d", &p.x);
                        } else if (!strcmp(attr.key, "y")){
                            sscanf(attr.value, "%d", &p.y);
                        } else if (!strcmp(attr.key, "angle")){
                            sscanf(attr.value, "%d", &oa->objectAngle);
                        } else {
                            if (IS_ERR_OPEN) ERR << "WARNING :: summonEntity; lights; light, reason : cannot reconize '" << attr.key << "' particle attribute" << endl;
                        }
                    }

                    if (light){
                        oa->angle = getAngleM(rect.w / 2, rect.h / 2, p.x, p.y) - 90;
                        oa->dist = getDistanceM(p.x, p.y, rect.w / 2, rect.h / 2);

                        this->lights.push_back(light);
                        lights_points.push_back(oa);
                        LIGHTS.push_back(light);
                    }

                } else {
                    if (IS_ERR_OPEN) ERR << "WARNING :: summonEntity; lights, reason : cannot reconize '" << light_node->tag << "' particles child" << endl;
                }
            }
        } else {
            if (IS_ERR_OPEN) ERR << "WARNING :: Entity::load_from_xml, reason : cannot reconize '" << child->tag << "' summonEntity child" << endl;
        }
    }

    updateEquipmentPos();
    return true;
}

void Entity::reset(void){
    if (IS_LOG_OPEN) LOG << "Entity::reset()" << endl;
    this->z = 0;
    this->angle = 0;

    this->speed=0;
    this->acceleration = 0;
    this->strength = 0;
    this->acceleration = 0;
    this->turn_strength = 0;
    this->turn_speed = 0;
    this->type = nullptr;
    
    if (onDeath) delete onDeath;

    for (int i=0; i<particles.size(); i++){
        delete particles_point[i];
        particles[i]->duration(0);
        particles_point[i] = nullptr;
    }
    particles.clear();
    particles_point.clear();

    /*
    for (int i=0; i<lights.size(); i++){
        delete lights[i];
        delete lights_points[i];
        lights[i] = nullptr;
        lights_points[i] = nullptr;
    }
    lights.clear();
    lights_points.clear();
    */
}

Entity::Entity(){
    if (IS_LOG_OPEN) LOG << "Entity::Entity()" << endl;
    equipments = nullptr;
    onDeath = NULL;
    reset();
}

Entity::Entity(bool isPlayer){
    if (IS_LOG_OPEN) LOG << "Entity::Entity()" << endl;
    equipments = nullptr;
    onDeath = NULL;
    reset();
    is_player = isPlayer;
}

Entity::~Entity(){
    if (IS_LOG_OPEN) LOG << "Entity::~Entity()" << endl;
    
    unlink();
    reset();
}

void Entity::update(){

    if (!onDeath){
        if (this->is_player){
            if (KEYPAD->getKey(PLAYER_CONTROL.engineUp)){
                this->strength = this->type->getStrength();
            } else if (KEYPAD->getKey(PLAYER_CONTROL.engineDown)){
                this->strength = -this->type->getStrength();
            } else {
                if (this->speed > 0.5f){
                    if (PLAYER_CONTROL.engineUP_type) this->strength = -this->type->getStrength();
                } else if (speed < 0.05f) {
                    if (PLAYER_CONTROL.engineDown_type) this->strength = this->type->getStrength();
                } else {
                    strength = 0;
                }
            }

            if (KEYPAD->getKey(PLAYER_CONTROL.turnLeft)){
                this->turn_strength = -this->type->getStrength();
            } else if (KEYPAD->getKey(PLAYER_CONTROL.turnRight)){
                this->turn_strength = this->type->getStrength();
            } else {
                if (this->turn_speed > 0.01){
                    if (PLAYER_CONTROL.turnRight_type) this->turn_strength = -this->type->getStrength();
                } else if (turn_speed < -0.01){
                    if (PLAYER_CONTROL.turnLeft_type) this->turn_strength = this->type->getStrength();
                } else {
                    turn_strength = 0;
                    turn_speed = 0;
                }
            }

            if (fabs(this->strength) > 1 && this->type->getMass() != 0){
                this->acceleration = this->strength / this->type->getMass();
            } else {
                this->acceleration = 0;
            }

            this->speed += this->acceleration * (MAINVAR->time.execTime);
            
            if (this->speed > this->type->getMaxSpeed()){
                this->speed = this->type->getMaxSpeed();
            } else if (this->speed < this->type->getMinSpeed()){
                this->speed = this->type->getMinSpeed();
            }

            if (this->turn_strength != 0 && this->type->getMass() != 0){
                this->turn_acceleration = this->turn_strength / (this->type->getMass() * this->type->getRect().h) * 2;
            } else {
                this->turn_acceleration = 0;
            }

            this->turn_speed += this->turn_acceleration * (MAINVAR->time.execTime);

            if (turn_speed > type->getMaxRotarySpeed()){
                turn_speed = type->getMaxRotarySpeed();
            } else if (turn_speed < -type->getMaxRotarySpeed()){
                turn_speed = -type->getMaxRotarySpeed();
            }

            if (KEYPAD->getKey(PLAYER_CONTROL.layerDown)){
                if (this->z > this->type->getLayerMin()) this->z --;
                
            } else if (KEYPAD->getKey(PLAYER_CONTROL.layerUp)){
                if (this->z < this->type->getLayerMax()) this->z ++;
            }

            for (int i=0; i<type->getEquipmentSize(); i++){
                if (equipments[i]) equipments[i]->setTarget(MOUSEPOS.x, MOUSEPOS.y);
            }
        }

        setParticlesPos();
        setLightsPos();
        updateEquipments();

        if (this->speed!=0){
            this->is_mouving = true;
            int x, y;
            setAngleM(&x, &y, this->speed, this->angle-90);
            this->rect.x += x;
            this->rect.y += y;
            
        } else {
            this->is_mouving = false;
        }

        if (this->turn_speed != 0){
            switch (type->getTurnType()){
                case TurnType::Turnfree:
                    this->angle += this->turn_speed;
                    break;
                
                case TurnType::Turnmul:
                    this->angle += this->turn_speed * type->getTurnValue();
                    break;
                
                case TurnType::Turndiv:
                    this->angle += this->turn_speed / type->getTurnValue();
                    break;
                
                case TurnType::Turnadd:
                    this->angle += this->turn_speed + type->getTurnValue();
                    break;
                
                case TurnType::Turnsub:
                    this->angle += this->turn_speed - type->getTurnValue();
                    break;
                
                default:
                    break;
            }
        }


    } else {
        z = (float)((SDL_GetTicks() - onDeath->tick) * (float)type->getDeath()->z) / (float)type->getDeath()->time;
    }
}

bool Entity::draw(){
    if (!this->type){
        if (IS_ERR_OPEN) ERR << "ERROR :: Entity::draw, reason : cannot draw a entity who is not linked to a type" << endl;
        return false;
    }


    SDL_Rect temp = {this->rect.x + CAMERA.x, this->rect.y + CAMERA.y, (int)(this->rect.w / ZOOM), (int)(this->rect.h / ZOOM)};
    if (SDL_RenderCopyEx(RENDERER, this->type->getTexture(), NULL, &temp, this->angle, 0, SDL_FLIP_NONE)){
        if (IS_ERR_OPEN) ERR << "ERROR :: SDL_RenderCopy, reason : " << SDL_GetError() << endl;
        return false;
    }

    if (IS_DEBUG){
        if (!drawHitbox()) return false;
        if (!drawEquipmentPoint()) return false;
    }

    
    for (int i=0; i<type->getEquipmentSize(); i++){
        if (equipments[i]){
            equipments[i]->draw();
        }
    }

    return true;
}

void Entity::unlink(void){
    if (IS_LOG_OPEN) LOG << "Entity::unlink()" << endl;
    this->angle = 0;
    this->speed = 0;

    delete[] part;
    delete[] equipmentsP;

    if (equipments){
        for (int e=0; e<type->getEquipmentSize(); e++){
            if (equipments[e]) delete equipments[e];
            equipments[e] = NULL;
        }
    }
    delete[] equipments;
    equipments = nullptr;
    
    this->type = nullptr;
}

void Entity::getPart(Point **p){
    (*p) = new Point[type->getPartSize()];
    for (int i=0; i<type->getPartSize(); i++){
        setAngleM(&(*p)[i].x, &(*p)[i].y, part[i].distFromCenter, part[i].additionnalAngle + angle + 90);
        (*p)[i].x += rect.x + CAMERA.x + (rect.w / 2);
        (*p)[i].y += rect.y + CAMERA.y + (rect.h / 2);
    }
}

void Entity::getEquipment(Point **p){
    (*p) = new Point[type->getEquipmentSize()];
    for (int i=0; i<type->getEquipmentSize(); i++){
        setAngleM(&(*p)[i].x, &(*p)[i].y, equipmentsP[i].distFromCenter, equipmentsP[i].additionnalAngle + angle + 90);
        (*p)[i].x += rect.x + CAMERA.x + (rect.w / 2);
        (*p)[i].y += rect.y + CAMERA.y + (rect.h / 2);
    }
}

bool Entity::drawHitbox(void){
    Sint16* x = new Sint16[type->getPartSize()];
    Sint16* y = new Sint16[type->getPartSize()];

    Point* p;
    getPart(&p);

    for (int i=0; i<type->getPartSize(); i++){
        x[i] = p[i].x;
        y[i] = p[i].y;
    }

    if (polygonRGBA(RENDERER, x, y, type->getPartSize(), 255, 0, 0, 255)){
        if (IS_ERR_OPEN) ERR << "ERROR :: polygonRGBA, reason : " << SDL_GetError() << endl;
        delete[] x;
        delete[] y;
        delete[] p;
        return false;
    }

    for (int i=0; i<type->getPartSize(); i++){
        if (filledCircleRGBA(RENDERER, x[i], y[i], 3, 255, 0, 0, 255)){
            if (IS_ERR_OPEN) ERR << "ERROR :: filledCircleRGBA, reason : " << SDL_GetError() << endl;
            delete[] x;
            delete[] y;
            delete[] p;
            return false;
        }
    }

    delete[] x;
    delete[] y;
    delete[] p;

    return true;
}

bool Entity::drawEquipmentPoint(void){

    Point* p;
    getEquipment(&p);

    for (int i=0; i<type->getEquipmentSize(); i++){
        if (filledCircleRGBA(RENDERER, p[i].x, p[i].y, 3, 0, 255, 0, 255)){
            if (IS_ERR_OPEN) ERR << "ERROR :: filledCircleRGBA, reason : " << SDL_GetError() << endl;
            return false;
        }

        if (pieRGBA(RENDERER, p[i].x, p[i].y, 30, type->getEquipment()[i].minAngle+angle-90, type->getEquipment()[i].maxAngle+angle-90, 0, 255, 0, 255)){
            if (IS_ERR_OPEN) ERR << "ERROR :: pieRGBA, reason : " << SDL_GetError() << endl;
            return false;
        }
    }

    delete[] p;
    return true;
}

void Entity::updateEquipmentPos(void){
    Point *p;
    getEquipment(&p);

    for (int i=0; i<type->getEquipmentSize(); i++){
        if (equipments[i]){
            equipments[i]->setPos(p[equipments[i]->id].x, p[equipments[i]->id].y);
        }
    }
    delete[] p;
}

bool Entity::drawLight(int i){
    if (i >= z-1 && i <= z+1){
        for (int e=0; e<type->getEquipmentSize() && equipments; e++){
            if (equipments[e]){
                equipments[e]->drawLight();
            }
        }
    }
    return true;
}

Entity_type* Entity::getType(void){
    return type;
}

bool Entity::in_screen(void){
    if (rect.x + CAMERA.x < WINDOW_WIDTH && rect.y + CAMERA.y < WINDOW_HEIGHT){
        if (rect.x + rect.w + CAMERA.x > 0 && rect.y + rect.h + CAMERA.y > 0){
            return true;
        }
    }
    return false;
}

void Entity::updateEquipments(void){
    updateEquipmentPos();
    for (int i=0; i<type->getEquipmentSize(); i++){
        if (equipments[i]){
            equipments[i]->update();
        }
    }
}

bool Entity::PointInside(int x, int y){
    Point* p;
    getPart(&p);

    if (isInside(p, type->getPartSize(), {x, y})){
        delete[] p;
        return true;
    }

    delete[] p;
    return false;
}

void Entity::setHealth(int health){
    this->health -= health;

    if (this->health <= 0){
        kill();
    }
}

void Entity::kill(void){
    if (!onDeath){
        onDeath = new OnDeath;
        onDeath->tick = SDL_GetTicks();
    }
}

bool Entity::should_delete(void){
    return (health <= 0 && (int)z == type->getDeath()->z);
}

void Entity::setParticlesPos(void){
    for (int i=0; i<particles.size(); i++){

        if (particles[i]){
            int x, y;
            setAngleM(&x, &y, particles_point[i]->dist, particles_point[i]->angle + angle);
            particles[i]->pos({x + rect.x + (rect.w / 2), y + rect.y + (rect.h / 2)});
            particles[i]->angle(particles_point[i]->objectAngle + angle);
            particles[i]->z(z);

        } else {
            particles.erase(particles.begin() + i);
            i--;
        }
    }
}

void Entity::setLightsPos(void){
    for (int i=0; i<lights.size(); i++){
        int x, y;
        setAngleM(&x, &y, lights_points[i]->dist, lights_points[i]->angle + angle);
        lights[i]->setPos(x + getCenteredX(), y + getCenteredY());
        lights[i]->setZ(z);
        lights[i]->setAngle(lights_points[i]->objectAngle + angle);
    }
}

int Entity::getCenteredX(void){
    return rect.x + (rect.w / 2) + CAMERA.x;
}

int Entity::getCenteredY(void){
    return rect.y + (rect.h / 2) + CAMERA.y;
}

int Entity::getHealth(void){
    return health;
}

Equipment** Entity::getEquipments(int* l){
    (*l) = type->getEquipmentSize();
    return equipments;
}

vector<Light*> Entity::getLights(void){
    return lights;
}