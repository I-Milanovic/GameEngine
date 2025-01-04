#include "MaterialCache.h"

//#include "string"

MaterialCache::MaterialCache() 
	: m_defaultMaterial(Material("defaultMaterial")) {
	m_materials.insert({ m_defaultMaterial.getMaterialName() ,m_defaultMaterial});	//todo reinstate later
}

void MaterialCache::addMaterial(Material material) {
	unsigned int counter = 0;
	std::string name = material.getMaterialName();
	bool flag = true;
	while (flag) {
		if (m_materials.contains(name)) {
			name += "_" + std::to_string(counter++);
		}
		else {
			m_materials.insert({ name ,material });
			flag = false;
		}
	}
}

void MaterialCache::addMaterials(const std::vector<Material>& materials) {
	for (Material material : materials)
		addMaterial(material);
}

Material& MaterialCache::getMaterial(std::string materialName) {
	return m_materials.at(materialName);
}

std::map<std::string, Material>& MaterialCache::getAll() {
	return m_materials;
}

const unsigned int MaterialCache::getSize() {
	return m_materials.size();
}
