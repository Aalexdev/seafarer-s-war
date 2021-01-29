#include "api/class/hitbox.hpp"
#include "main.hpp"

void HitPoint::calculate(Point *center, int &angle){
    int agl = 0;
    if (angle){
        agl = angle;
    }

    Point ctr = {0, 0};

    if (center){
        ctr = (*center);
    }

    this->distFromCenter = getDistanceM(this->x, this->y, ctr.x, ctr.y);
    this->angle = getAngleM(this->x, this->y, ctr.x, ctr.y) + agl;

    setAngleM(&this->x, &this->y, this->distFromCenter, this->angle);
}

Hitbox::Hitbox(){
    this->color = (SDL_Color){255,255,255,255};
    this->hitPoints.clear();
}

Hitbox::~Hitbox(void){
    for (HitPoint* point : this->hitPoints){
        if (point) delete point;
    }

    this->hitPoints.clear();
}

bool Hitbox::read_from_xml(XMLNode* node){

    if (!node){
        cerr << "cannot load a NULL node : " << __FILE__ << ";" << __LINE__ << endl;
        return false;
    }

    for (int i=0; i<node->children.size; i++){
        XMLNode *child = XMLNode_child(node, i);

        if (strcmp(child->tag, "point")){
            HitPoint *point = new HitPoint;

            for (int a=0; a<child->attributes.size; a++){
                XMLAttribute attr = child->attributes.data[a];

                if (!strcmp(attr.key, "x")){
                    sscanf(attr.value, "%d", &point->x);
                } else if (!strcmp(attr.key, "y")){
                    sscanf(attr.value, "%d", &point->y);
                } else {
                    cout << "cannot reconize '" << attr.key << "' point attribute"<< endl;
                }
            }

            this->hitPoints.push_back(point);
        }
    }

    return true;
}

void Hitbox::push(HitPoint *pnt){
    this->hitPoints.push_back(pnt);
}

void Hitbox::pop(void){
    this->hitPoints.pop_back();
}

void Hitbox::reload_rect(void){
    this->rect.w = 0;
    this->rect.h = 0;
    if (this->hitPoints.empty()){
        
        return;
    }

    for (HitPoint* point : this->hitPoints){
        if (point->x > this->rect.w) this->rect.w = point->x;
        if (point->y > this->rect.h) this->rect.h = point->y;
    }
}

bool Hitbox::draw(void){

    if (this->hitPoints.empty()) return true;

    int x=0, y=0, index=0;
    
    SDL_SetRenderDrawColor(RENDERER, this->color.r, this->color.g, this->color.b, this->color.a);
    for (HitPoint *point : this->hitPoints){

        if (index == 0){
            x = this->hitPoints.back()->x;
            y = this->hitPoints.back()->y;
        }

        if (SDL_RenderDrawLine(RENDERER, x, y, point->x, point->y)){
            cerr << "SDL_RenderDrawLine Error : " << SDL_GetError() << endl;
            return false;
        }

        x = point->x;
        y = point->y;

        index++;
    }

    SDL_SetRenderDrawColor(RENDERER, 0, 0, 0, 0);
    return true;
}

void Hitbox::setDrawColor(SDL_Color new_color){
    this->color = new_color;
}

bool Hitbox::is_point_inside(Point point){
    if (this->hitPoints.empty()) return false;

    Point *polygone = new Point[this->hitPoints.size()];

    if (!polygone){
        cerr << "malloc error" << endl;
        return false;
    }

    int i = 0;

    for (HitPoint *pnt : this->hitPoints){
        polygone[i].x = pnt->x;
        polygone[i].y = pnt->y;
        i++;
    }

    return isInside(polygone, this->hitPoints.size(), point);
}

bool Hitbox::is_collide(Hitbox *hitbox){
    if (this->hitPoints.empty()) return false;

    Point *polygone = new Point[this->hitPoints.size()];

    if (!polygone){
        cerr << "malloc error" << endl;
        return false;
    }

    int i = 0;

    for (HitPoint *pnt : this->hitPoints){
        polygone[i].x = pnt->x;
        polygone[i].y = pnt->y;
        i++;
    }

    for (HitPoint* pnt : hitbox->hitPoints){
        Point p = {pnt->x, pnt->y};
        if (isInside(polygone, this->hitPoints.size(), p)) return true;
    }

    return false;
}

void Hitbox::clear(void){
    this->hitPoints.clear();
}