/*
 Copyright (C) 2010-2013 Kristian Duske
 
 This file is part of TrenchBroom.
 
 TrenchBroom is free software: you can redistribute it and/or modify
 it under the terms of the GNU General Public License as published by
 the Free Software Foundation, either version 3 of the License, or
 (at your option) any later version.
 
 TrenchBroom is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU General Public License for more details.
 
 You should have received a copy of the GNU General Public License
 along with TrenchBroom.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "CreateBrushTool.h"

#include "Model/Brush.h"
#include "Model/HitFilters.h"
#include "Model/Picker.h"
#include "Renderer/Camera.h"
#include "View/InputState.h"
#include "View/MapDocument.h"

namespace TrenchBroom {
    namespace View {
        CreateBrushTool::CreateBrushTool(BaseTool* next, MapDocumentPtr document) :
        Tool(next),
        m_document(document) {}

        bool CreateBrushTool::doStartPlaneDrag(const InputState& inputState, Plane3& plane, Vec3& initialPoint) {
            if (!inputState.mouseButtonsPressed(MouseButtons::MBLeft) ||
                !m_document->hasSelectedObjects())
                return false;
            
            Model::HitFilterChain hitFilter = Model::chainHitFilters(Model::TypedHitFilter(Model::Brush::BrushHit), Model::DefaultHitFilter(inputState.filter()));
            const Model::PickResult::FirstHit first = inputState.pickResult().firstHit(hitFilter, true);
            if (first.matches)
                initialPoint = first.hit.hitPoint();
            else
                initialPoint = inputState.camera().defaultPoint(inputState.pickRay().direction);

            plane = Plane3(Vec3::PosZ, initialPoint);
            m_initialPoint = initialPoint;

            return true;
        }
        
        void CreateBrushTool::doResetPlane(const InputState& inputState, Plane3& plane, Vec3& initialPoint) {
        }
        
        bool CreateBrushTool::doPlaneDrag(const InputState& inputState, const Vec3& lastPoint, const Vec3& curPoint, Vec3& refPoint) {
        }
        
        void CreateBrushTool::doEndPlaneDrag(const InputState& inputState) {
        }
        
        void CreateBrushTool::doCancelPlaneDrag(const InputState& inputState) {
        }
    }
}
