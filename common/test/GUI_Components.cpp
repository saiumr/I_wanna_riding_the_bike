//
// Created by 桂明谦 on 2020/1/6.
//

#include "guitestframework.hpp"
#include "engin/gui/guiresourcemanager.hpp"
#include "engin/gui/button.hpp"
#include "engin/gui/imagebutton.hpp"
#include "engin/gui/checkbox.hpp"
#include "engin/gui/radiobutton.hpp"
#include "engin/gui/slidebar.hpp"

using namespace GUI;

class GUI_Test:public GUITestframework{
public:
    GUI_Test():GUITestframework("GUI components", 800, 600, SDL_WINDOW_SHOWN),slideBar(100, 500){
        GUIResourceManager::InitGUI(render);
        button.SetText("button1");
        button.Move(100, 200);
        button.Resize(100, 60);
        imagebutton.SetText("Image Button");
        imagebutton.Move(100, 400);
        imagebutton.SetImage(IMG_LoadTexture(render, "resources/test/button_normalbgimage.png"), IMG_LoadTexture(render, "resources/test/button_pressbgimage.png"));
        imagebutton.Resize(200, 150);
        checkBoxGroup.SetTopLeft(100, 100);
        checkBoxGroup.SetItemAlignType(CheckBoxGroup::ItemAlignType::VERTICAL);
        checkBoxGroup.SetTextWarpType(CheckBoxGroup::TextWarpType::RIGHT);
        checkBoxGroup.Append(std::move(CheckBox("checkbutton1", false)));
        checkBoxGroup.Append(CheckBox("checkbutton2", true));
        checkBoxGroup.Append(CheckBox("checkbutton3", false));

        radioButtonGroup.SetTopLeft(400, 100);
        radioButtonGroup.SetItemAlignType(RadioButtonGroup::ItemAlignType::VERTICAL);
        radioButtonGroup.SetTextWarpType(RadioButtonGroup::TextWarpType::LEFT);
        radioButtonGroup.Append(RadioButton("radio button1"));
        radioButtonGroup.Append(RadioButton("radio button2"));
        radioButtonGroup.Append(RadioButton("radio button3"));

        slideBar.SetType(SlideBar::Type::VERTICAL);
        slideBar.Move(400, 300);
        slideBar.SetValue(50);
    }

    void EventHandle(SDL_Event& event) override{
        GUITestframework::EventHandle(event);
        button.EventHandle(event);
        imagebutton.EventHandle(event);
        checkBoxGroup.EventHandle(event);
        radioButtonGroup.EventHandle(event);
        slideBar.EventHandle(event);
    }

    void Update() override{
        if(button.QueryState(Button::RELEASED))
            SDL_LogInfo(SDL_LOG_CATEGORY_APPLICATION, "clicked");

        //GUI Update must at the end
        button.Update();
        imagebutton.Update();
        checkBoxGroup.Update();
        radioButtonGroup.Update();
        slideBar.Update();
    }
    ~GUI_Test(){
        SDL_DestroyTexture(imagebutton.GetPressImage());
        SDL_DestroyTexture(imagebutton.GetNormalImage());
    }
private:
    ImageButton imagebutton;
    Button button;
    CheckBoxGroup checkBoxGroup;
    RadioButtonGroup radioButtonGroup;
    SlideBar slideBar;
};

RUN_APP(GUI_Test)
