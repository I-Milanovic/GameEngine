#include "LightUi.h"

#include "string"
#include <iostream>

LightUi::LightUi(SceneLights& sceneLights) : m_sceneLights(sceneLights) {
    static bool alpha_preview = false;
    static bool alpha_half_preview = false;
    static bool drag_and_drop = true;
    static bool options_menu = true;
    static bool hdr = false;

    m_misc_flags = (hdr ? ImGuiColorEditFlags_HDR : 0) | (drag_and_drop ? 0 : ImGuiColorEditFlags_NoDragDrop) |
        (alpha_half_preview ? ImGuiColorEditFlags_AlphaPreviewHalf : (alpha_preview ? ImGuiColorEditFlags_AlphaPreview : 0)) |
        (options_menu ? 0 : ImGuiColorEditFlags_NoOptions);
}

void LightUi::RenderLightUi() {
//	ImGui::Begin("Lighting");
    RenderAmbientLightUi();
    RenderDirectionalLightUi();
    RenderPointLightUi();
  //  RenderSpotLightUi();
//	ImGui::End();
}

void LightUi::RenderAmbientLightUi() {
    float ambientStepVal = 0.005f;
    glm::vec3& ambientColor = m_sceneLights.getAmbientLight().m_color;
    float& ambientIntensity = m_sceneLights.getAmbientLight().m_factor;
    
    ImGui::SeparatorText("Ambient Light");
    ImGui::ColorEdit3("##AmbientColor", (float*)&ambientColor, m_misc_flags);
    ImGui::DragFloat("##AmbientIntensity", &ambientIntensity, ambientStepVal, 0.0f, 10.0f, "Factor: %.3f");
}

void LightUi::RenderDirectionalLightUi() {
    DirLight& dirLight = m_sceneLights.getDirLight();
    glm::vec3& dirPos = dirLight.m_direction;
    glm::vec3& dirColor = dirLight.m_color;
    float& dirIntensity = dirLight.m_intensity;

    float sliderStep = 0.005f;
    ImGui::SeparatorText("Directional Light");
    ImGui::ColorEdit3("##DirColor", (float*)&dirColor, m_misc_flags);
    ImGui::DragFloat("##DirIntensity", &dirIntensity, sliderStep, 0.0f, 10.0f, "Factor: %.3f");
    ImGui::DragFloat("##XcameraPos", &dirPos.x, sliderStep, 0.0f, 0.0f, "X: %.3f");
    //   ImGui::SameLine();
    ImGui::DragFloat("##YcameraPos", &dirPos.y, sliderStep, 0.0f, 0.0f, "Y: %.3f");
    //   ImGui::SameLine();
    ImGui::DragFloat("##ZcameraPos", &dirPos.z, sliderStep, 0.0f, 0.0f, "Z: %.3f");
}

void LightUi::RenderPointLightUi() {
    int item_current_idx = 0;                                        // Here we store our selection data as an index.
    std::vector<PointLight>& l = m_sceneLights.getPointLights();
    int numOfLights = l.size();
    bool isPointLightsEmpty = numOfLights <= 0 ? true : false;              // for disabling input if there are none light objects
    bool isMaxPointLightsReached = numOfLights < 5 ? false : true;          // setting max number of point lights

    ImGui::SeparatorText("Point Light");
    ImGui::BeginDisabled(isPointLightsEmpty);

    if (ImGui::Button("Remove")) {
        item_current_idx = 0;
        m_sceneLights.removePointLight(item_current_idx);
        numOfLights = l.size(); // update for later checks in program
    }
    ImGui::EndDisabled();

    ImGui::BeginDisabled(isMaxPointLightsReached);
    ImGui::SameLine();
    if (ImGui::Button("Add"))
       m_sceneLights.addPointLight(PointLight());
    ImGui::EndDisabled();

    if (ImGui::BeginListBox("listbox 1", ImVec2(-FLT_MIN, 5 * ImGui::GetTextLineHeightWithSpacing()))) {
        for (int n = 0; n < l.size(); n++) {
            const bool is_selected = (item_current_idx == n);
            std::string s = std::to_string(n);
            std::string a = "Point Light " + s;
            if (ImGui::Selectable(a.c_str(), is_selected))
                item_current_idx = n;

            // Set the initial focus when opening the combo (scrolling + keyboard navigation focus)
            if (is_selected)
                ImGui::SetItemDefaultFocus();
        }
        ImGui::EndListBox();
    }

    static glm::vec3 defValCol = glm::vec3(0.0f, 0.0f, 0.0f);
    static glm::vec3 defVal = glm::vec3(0.0f, 0.0f, 0.0f);
    static float defFloat = 1.0f;

    static glm::vec3* pointColor = &defValCol;
    static float* pointIntensity = &defFloat;
    static glm::vec3* pointPosition = &defVal;

    if (numOfLights > 0) {
        PointLight& pLight = m_sceneLights.getPointLights().at(item_current_idx);
        pointColor = &pLight.m_color;
        pointIntensity = &pLight.m_intensity;
        pointPosition = &pLight.m_position;
    }
    else {
        pointColor = &defValCol;
        pointIntensity = &defFloat;
        pointPosition = &defVal;
    }

    ImGui::BeginDisabled(isPointLightsEmpty);
    static float pointStepVal = 0.25;
    ImGui::ColorEdit3("##PointColor", (float*)pointColor, m_misc_flags);
    ImGui::DragFloat("##PointIntensity", pointIntensity, pointStepVal, 0.0f, 10.0f, "Factor: %.3f");

    static float val4 = 0.0f; // still in use, no quaternions implemented
    float pointPosSpd = 0.05f;
    ImGui::DragFloat("##XPoint", &pointPosition->x, pointPosSpd, 0.0f, 0.0f, "X: %.3f");
    ImGui::DragFloat("##YPoint", &pointPosition->y, pointPosSpd, 0.0f, 0.0f, "Y: %.3f");
    ImGui::DragFloat("##ZPoint", &pointPosition->z, pointPosSpd, 0.0f, 0.0f, "Z: %.3f");
    ImGui::DragFloat("##WPoint", &val4, pointPosSpd, 0.0f, 0.0f, "W: %.3f");
    ImGui::EndDisabled();
}

void LightUi::RenderSpotLightUi() {
    int item_current_idx = 0; // Here we store our selection data as an index.
    std::vector<SpotLight>& l = m_sceneLights.getSpotLights();
    int numOfLights = l.size();
    bool isSpotLightsEmpty = numOfLights <= 0 /*&& numOfLights <= 5*/ ? true : false;         // for disabling input if there are none light objects
    bool isMaxSpotLights = false;


    //if (l.size() <= 0)
    //    isSpotLightsEmpty = true;
    //else
    //    isSpotLightsEmpty = false;

    ImGui::SeparatorText("Spot Light");
    ImGui::BeginDisabled(isSpotLightsEmpty);
    if (ImGui::Button("Remove##Spot"))
        m_sceneLights.removeSpotLight(item_current_idx);
    ImGui::EndDisabled();


    if (l.size() >= 5)
        isMaxSpotLights = true;
    else
        isMaxSpotLights = false;

    ImGui::BeginDisabled(isMaxSpotLights);
    ImGui::SameLine();
    if (ImGui::Button("Add##Spot"))
        m_sceneLights.addSpotLight(SpotLight());
    ImGui::EndDisabled();

    if (ImGui::BeginListBox("SpotLightListBox", ImVec2(-FLT_MIN, 5 * ImGui::GetTextLineHeightWithSpacing()))) {
        for (int n = 0; n < l.size(); n++) {
            const bool is_selected = (item_current_idx == n);
            std::string s = std::to_string(n);
            std::string a = "Spot Light " + s;
            if (ImGui::Selectable(a.c_str(), is_selected))
                item_current_idx = n;

            // Set the initial focus when opening the combo (scrolling + keyboard navigation focus)
            if (is_selected)
                ImGui::SetItemDefaultFocus();
        }
        ImGui::EndListBox();
    }

    static glm::vec3 defConeCol = glm::vec3(0.0f, 0.0f, 0.0f);
    static glm::vec3 defValCol = glm::vec3(0.0f, 0.0f, 0.0f);
    static glm::vec3 defVal = glm::vec3(0.0f, 0.0f, 0.0f);
    static float defFloat = 1.0f;

    static glm::vec3* spotColor = &defValCol;
    static float* spotIntensity = &defFloat;
    static glm::vec3* spotPosition = &defVal;
    static glm::vec3* spotConeDir = &defConeCol;
    static float* spotCutOff = &defFloat;

    static bool isSpotAttDisabled = true;
    if (m_sceneLights.getSpotLights().size() > 0) {
        SpotLight& sLight = m_sceneLights.getSpotLights().at(item_current_idx);
        spotColor = &sLight.m_pointLight.m_color;
        spotIntensity = &sLight.m_pointLight.m_intensity;
        spotPosition = &sLight.m_pointLight.m_position;
        spotConeDir = &sLight.m_coneDir;
        spotCutOff = &sLight.m_cutOff;

        isSpotAttDisabled = false;
    }
    else {
        spotColor = &defValCol;
        spotIntensity = &defFloat;
        spotPosition = &defVal;
        isSpotAttDisabled = true;
    }

    ImGui::BeginDisabled(isSpotAttDisabled);
    static float pointStepVal = 0.25;
    ImGui::ColorEdit3("##SpotColor", (float*)spotColor, m_misc_flags);
    ImGui::DragFloat("##SpotIntensity", spotIntensity, pointStepVal, 0.0f, 10.0f, "Factor: %.3f");

    static float val4 = 0.0f; // still in use, no quaternions implemented
    float pointPosSpd = 0.05f;
    ImGui::DragFloat("##XSpot", &spotPosition->x, pointPosSpd, 0.0f, 0.0f, "X: %.3f");
    ImGui::DragFloat("##YSpot", &spotPosition->y, pointPosSpd, 0.0f, 0.0f, "Y: %.3f");
    ImGui::DragFloat("##ZSpot", &spotPosition->z, pointPosSpd, 0.0f, 0.0f, "Z: %.3f");
    ImGui::DragFloat("##WSpot", &val4, pointPosSpd, 0.0f, 0.0f, "W: %.3f");
    ImGui::EndDisabled();


}
