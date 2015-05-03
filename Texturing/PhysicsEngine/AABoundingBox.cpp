#include "AABoundingBox.h"


AABoundingBox::AABoundingBox()
{
	SetCenter(glm::vec3(0));
	SetSize(glm::vec3(0));
}

AABoundingBox::AABoundingBox(glm::vec3 fCenter, glm::vec3 fSize)
{
	SetCenter(fCenter);
	SetSize(fSize);
}

AABoundingBox::~AABoundingBox(void)
{

}

void AABoundingBox::SetCenter(glm::vec3 fCenter)
{
	center = fCenter;
}

void AABoundingBox::SetSize(glm::vec3 fSize)
{
	size = fSize;
	halfSize = size/2.0f;
}

bool AABoundingBox::IsIntersecting(AABoundingBox& box)
{
	glm::vec3 absoluteDistance = glm::abs( this->center - box.GetCenter());
	glm::vec3 totalHalfSize = this->GetHalfSize() + box.GetHalfSize();
	if(		absoluteDistance.x < totalHalfSize.x
		&&	absoluteDistance.y < totalHalfSize.y
		&&	absoluteDistance.z < totalHalfSize.z)
	{
		return true;
	}
	return false;
}

glm::vec3 AABoundingBox::GetIntersectionDepth(AABoundingBox& box)
{
	glm::vec3 absoluteDistance = glm::abs( this->center - box.GetCenter());
	glm::vec3 totalHalfSize = this->GetHalfSize() + box.GetHalfSize();
	glm::vec3 depth = totalHalfSize - absoluteDistance;
	return depth;
}

void AABoundingBox::Scale(glm::vec3 scale)
{
	glm::vec3 scaledSize = this->size * scale;
	glm::vec3 scaledCenter = this->center *scale;
	SetSize(scaledSize);
	SetCenter(scaledCenter);
}

void AABoundingBox::Scale(float scaleX,float scaleY, float scaleZ)
{
	glm::vec3 scale = glm::vec3(scaleX,scaleY,scaleZ);
	Scale(scale);
}

void AABoundingBox::Translate(glm::vec3 translation)
{
	glm::vec3 translatedCenter = this->center + translation;
	SetCenter(translatedCenter);
}

void AABoundingBox::Translate(float translateX, float translateY, float translateZ)
{
	glm::vec3 translation = glm::vec3(translateX,translateY,translateZ);
	Translate(translation);
}

void AABoundingBox::Rotate(glm::mat4 rotationMatrix)
{
	// Untested Solution
	std::vector<glm::vec3> corners;
	int numberOfCorners = 4;
	corners.resize(numberOfCorners);
	for (int i = 0; i < corners.size(); i++)
	{
		corners[i] = halfSize;
	}
	corners[1].y *= -1;
	corners[2].z *= -1;
	corners[3].y *= -1;
	corners[3].z *= -1;
	for (int i = 0; i < corners.size(); i++)
	{
		corners[i] = glm::vec3(rotationMatrix*glm::vec4(corners[i],1));
	}
	for (int i = 0; i < numberOfCorners; i++)
	{
		corners.push_back(corners[i] *-1.0f);
	}
	glm::vec3 cornersBoxSize = CalculateBoundingBoxSize(corners);
	SetSize(cornersBoxSize);	
}

void AABoundingBox::Rotate(float angle,float axisX,float axisY, float axisZ)
{
	glm::mat4 rotationMatrix = glm::rotate(angle,axisX,axisY,axisZ);
	Rotate(rotationMatrix);
}

glm::vec3 AABoundingBox::CalculateBoundingBoxSize(const std::vector<glm::vec3>& vertices)
{
	glm::vec3 boxMin = glm::vec3( 99999999.0f);
	glm::vec3 boxMax = glm::vec3(-99999999.0f);

	for (int i = 0; i < vertices.size(); i++)
	{
		//check each dimension
		for (int j = 0; j < 3; j++)
		{
			if (boxMin[j] > vertices[i][j])
			{
				boxMin[j] = vertices[i][j];
			}
			if (boxMax[j] < vertices[i][j])
			{
				boxMax[j] = vertices[i][j];
			}
		}
	}
	glm::vec3 boxCenter = (boxMax + boxMin)/2.0f;
	glm::vec3 boxSize = boxMax - boxMin;

	if (boxSize.x <0.0f || boxSize.y<0.0f || boxSize.z<0.0f)
	{
		throw std::runtime_error("ERROR: bounding box size cannot be less than zero!");
	}
	
	return boxSize;
}