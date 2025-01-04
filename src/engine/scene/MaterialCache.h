#pragma once
#include <vector>
#include <map>
#include <string>

#include "Material.h"


class MaterialCache {

public:
	MaterialCache();
	void addMaterial(Material material);
	void addMaterials(const std::vector<Material>& materials);
	Material& getMaterial(std::string materialName);
	std::map<std::string,  Material>& getAll();
	const unsigned int getSize();

private:
	Material m_defaultMaterial;
	std::map<std::string, Material> m_materials;
//	std::vector<Material> m_materials;
};
