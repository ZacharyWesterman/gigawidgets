#include "single_child_element.hpp"
#include "../core/display.hpp"

namespace ui {

SingleChildElement::SingleChildElement(Element *const child, const Position &pos, const Alignment &align, const Padding &padding) : child(child), Element(pos, align, padding) {
	child->setParent(this);
}

SingleChildElement::~SingleChildElement() {
	delete child;
}

Size SingleChildElement::size() const {
	return child->size();
}

void SingleChildElement::drawDone() {
	Element::drawDone();
	child->drawDone();
}

void SingleChildElement::setChild(Element *const child) {
	delete this->child;
	this->child = child;
	child->setParent(this);
}

bool SingleChildElement::handleEvent(const Event &event) {
	if (Element::handleEvent(event)) {
		child->handleEvent(event);
	}
}

bool SingleChildElement::update(time_t time_ms) {
	return child->update(time_ms) || child->redrawRequested() || rotationChanged();
}

} // namespace ui
