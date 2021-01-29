#include "ui/widgets/widget.hpp"
#include "main.hpp"

Widget::Widget(){
    this->hitbox = new Hitbox();
}

Widget::~Widget(){
    if (this->hitbox){
        delete this->hitbox;
    }
}

bool Widget::set_hitbox(Hitbox* new_hitbox){
    if (!new_hitbox){
        if (IS_ERR_OPEN) ERR << "ERROR :: Widget::set_hitbox, reason : cannot set a null hitbox" << endl;
        return false;
    }

    this->hitbox = new_hitbox;
    return true;
}

void Widget::add_hitPoint(int x, int y){
    HitPoint *p = new HitPoint();
    p->x = x;
    p->y = y;
    this->hitbox->push(p);
}

void Widget::add_hitPoint(HitPoint *pnt){
    this->hitbox->push(pnt);
}

void Widget::add_hitPoint(Point p){
    HitPoint *hp = new HitPoint();

    hp->x = p.x;
    hp->y = p.y;

    this->hitbox->push(hp);
}

void Widget::clear_hitbox(void){
    this->hitbox->clear();
}

void Widget::pop_hitPoint(void){
    this->hitbox->pop();
}

void Widget::draw_hitbox(void){
    this->hitbox->draw();
}

bool Widget::is_mouse_inside(void){
    if (this->hitbox->is_point_inside(MOUSEPOS)){
        return true;
    }
    return false;
}