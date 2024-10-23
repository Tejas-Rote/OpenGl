#ifndef CIRCLE_H
#define CIRCLE_H

#include <shap.h>

class Circle : public Shape {
public:
	Circle(float x, float y, float radius, int segments);
	~Circle();

	void create() override;
	void draw() override;

private:
	float x, y;
	float radius;
	int segments;
};


#endif // !CIRCLE_H
