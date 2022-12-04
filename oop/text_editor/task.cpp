#include "task.h"
#include "logged_command_wrapper.h"
CommandLoggerVisitor::CommandLoggerVisitor(std::ostream &logStream):logStream_(logStream){}

void CommandLoggerVisitor::VisitInsertTextCommand(InsertTextCommand &command) {
    this->logStream_<<'i';
}
void CommandLoggerVisitor::VisitMoveCursorLeftCommand(MoveCursorLeftCommand &command) {
    this->logStream_<<'h';
}
void CommandLoggerVisitor::VisitMoveCursorRightCommand(MoveCursorRightCommand &command) {
    this->logStream_<<'l';
}
void CommandLoggerVisitor::VisitMoveCursorUpCommand(MoveCursorUpCommand &command) {
    this->logStream_<<'k';
}
void CommandLoggerVisitor::VisitMoveCursorDownCommand(MoveCursorDownCommand &command) {
    this->logStream_<<'j';
}
void CommandLoggerVisitor::VisitSelectCommand(SelectTextCommand &command) {
    this->logStream_<<'v';
}
void CommandLoggerVisitor::VisitDeleteTextCommand(DeleteTextCommand &command) {
    this->logStream_<<'d';
}
void CommandLoggerVisitor::VisitCopyTextCommand(CopyTextCommand &command) {
    this->logStream_<<'y';
}
void CommandLoggerVisitor::VisitPasteTextCommand(PasteTextCommand &command) {
    this->logStream_<<'p';
}
void CommandLoggerVisitor::VisitUppercaseTextCommand(UppercaseTextCommand &command) {
    this->logStream_<<'U';
}
void CommandLoggerVisitor::VisitLowercaseTextCommand(LowercaseTextCommand &command) {
    this->logStream_<<'u';
}
void CommandLoggerVisitor::VisitMoveToEndCommand(MoveToEndCommand &command) {
    this->logStream_<<'$';
}
void CommandLoggerVisitor::VisitMoveToStartCommand(MoveToStartCommand &command) {
    this->logStream_<<'0';
}
void CommandLoggerVisitor::VisitDeleteWordCommand(DeleteWordCommand &command) {
    this->logStream_<<"dE";
}



/* Курсор влево */
class MoveCursorLeftCommand : public ICommand {
public:
    MoveCursorLeftCommand()=default;
    void Apply(std::string& buffer, size_t& cursorPosition, std::string& clipboard, TextEditor& editor) override{
        if(cursorPosition!=0){
            cursorPosition-=1;
            if(buffer[cursorPosition]=='\n')
                cursorPosition--;}
        if(editor.HasSelection())
            editor.UnselectText();
    }
    void AcceptVisitor(CommandVisitor& visitor) override{
        visitor.VisitMoveCursorLeftCommand(*this);
    }
};

/* Курсор вправо */
class MoveCursorRightCommand : public ICommand {
public:
    MoveCursorRightCommand()=default;
    void Apply(std::string& buffer, size_t& cursorPosition, std::string& clipboard, TextEditor& editor) override{
        if(cursorPosition!=buffer.size()-1){
            cursorPosition+=1;
            if(buffer[cursorPosition]=='\n')
                cursorPosition++;}
        else
            cursorPosition++;
        if(editor.HasSelection())
            editor.UnselectText();
    }
    void AcceptVisitor(CommandVisitor& visitor) override{
        visitor.VisitMoveCursorRightCommand(*this);
    }
};
/* Курсор вверх */
class MoveCursorUpCommand : public ICommand {
public:
    MoveCursorUpCommand()=default;
    void Apply(std::string& buffer, size_t& cursorPosition, std::string& clipboard, TextEditor& editor) override {
        size_t count_from_start=0;
        if(cursorPosition!=0){
            cursorPosition = buffer[cursorPosition]!='\n'?cursorPosition:cursorPosition-1;
            while(cursorPosition!=0 and buffer[cursorPosition]!='\n'){
                --cursorPosition;
                ++count_from_start;
            }
            if(buffer[cursorPosition]=='\n'){
                //count_from_start+=1;
                --cursorPosition;
                while(cursorPosition!=0 and buffer[cursorPosition]!='\n'){
                    --cursorPosition;
                }
                if(buffer[cursorPosition]=='\n')cursorPosition++;
                else
                    count_from_start--;
                // cursorPosition=buffer[cursorPosition]=='\n'?cursorPosition++:cursorPosition;
                //cursorPosition+=count_from_start;
            }

            cursorPosition+=count_from_start;
        }



        if(editor.HasSelection())
            editor.UnselectText();
    }
    void AcceptVisitor(CommandVisitor& visitor) override{
        visitor.VisitMoveCursorUpCommand(*this);
    }

};

/* Курсор вниз */
class MoveCursorDownCommand : public ICommand {
public:
    MoveCursorDownCommand()=default;
    void Apply(std::string& buffer, size_t& cursorPosition, std::string& clipboard, TextEditor& editor) override{
        size_t count_from_start=0;
        size_t s= cursorPosition;
        if(buffer[cursorPosition]!='\n' ) {
            while (buffer[cursorPosition] != '\n' and cursorPosition!=buffer.size()-1) {
                size_t prev_cursor_position=cursorPosition;
                while (buffer[prev_cursor_position] != '\n' and prev_cursor_position!=0) {
                    prev_cursor_position -= 1;
                    count_from_start += 1;
                }
                while (buffer[cursorPosition] != '\n' and cursorPosition!=buffer.size()-1) {
                    cursorPosition += 1;

                }
            }

            cursorPosition+=1;
        }
        else {
            cursorPosition += 1;
            while (buffer[cursorPosition] != '\n' and cursorPosition!=buffer.size()-1 ) {
                cursorPosition += 1;
            }

            cursorPosition+=1;
        }
        if(s!=0){
            cursorPosition+=count_from_start;}
        if(editor.HasSelection())
            editor.UnselectText();

    }
    void AcceptVisitor(CommandVisitor& visitor)override{
        visitor.VisitMoveCursorDownCommand(*this);
    }
};

/* Выделить текст */
class SelectTextCommand : public ICommand {
public:
    explicit SelectTextCommand(size_t selectionSize):selectionSize_(selectionSize){}
    void Apply(std::string& buffer, size_t& cursorPosition, std::string& clipboard, TextEditor& editor) override{
        editor.SelectText(cursorPosition,cursorPosition+this->selectionSize_);

    }
    void AcceptVisitor(CommandVisitor& visitor)override{
        visitor.VisitSelectCommand(*this);

    }

private:
    size_t selectionSize_;
};

/* Ввести текст */
class InsertTextCommand : public ICommand {
public:
    explicit InsertTextCommand(std::string text):text_(std::move(text)) { };
    void Apply(std::string& buffer, size_t& cursorPosition, std::string& clipboard, TextEditor& editor) override{
        if(this->text_[0]=='\n' and buffer[cursorPosition-1]=='\n'){
            buffer=buffer.substr(0, cursorPosition-1)+this->text_+buffer.substr(cursorPosition,buffer.size());
            cursorPosition+=text_.size()-1;
        }
        else{
            buffer=buffer.substr(0, cursorPosition)+this->text_+buffer.substr(cursorPosition,buffer.size());
            cursorPosition+=text_.size()-1;
        }
        if(this->text_[0]=='\n'){
            buffer+='\n';
        }
        else
            cursorPosition+=1;
        if(editor.HasSelection())
            editor.UnselectText();


    }
    void AcceptVisitor(CommandVisitor& visitor) override{
        visitor.VisitInsertTextCommand(*this);
    }

private:
    std::string text_;
};

/* Удалить текст */
class DeleteTextCommand : public ICommand {
public:
    DeleteTextCommand()=default;
    void Apply(std::string& buffer, size_t& cursorPosition, std::string& clipboard, TextEditor& editor) override{
        if(editor.HasSelection()){
            buffer=buffer.substr(0,editor.GetSelection().first)+buffer.substr(editor.GetSelection().second,buffer.size()-editor.GetSelection().second);
            editor.UnselectText();}
        else
            buffer=  buffer.substr(0,cursorPosition)+buffer.substr(cursorPosition,buffer.size()-cursorPosition);

    }
    void AcceptVisitor(CommandVisitor& visitor) override{
        visitor.VisitDeleteTextCommand(*this);
    }

};

/* Скопировать текст */
class CopyTextCommand : public ICommand {
public:
    CopyTextCommand()=default;
    void Apply(std::string& buffer, size_t& cursorPosition, std::string& clipboard, TextEditor& editor) override{
        if(editor.HasSelection())
            clipboard=buffer.substr(editor.GetSelection().first,editor.GetSelection().second - editor.GetSelection().first);
        else
            clipboard=buffer[cursorPosition];
        if(editor.HasSelection())
            editor.UnselectText();
    }
    void AcceptVisitor(CommandVisitor& visitor) override{
        visitor.VisitCopyTextCommand(*this);

    }

};

/* Вставить скопированный текст */
class PasteTextCommand : public ICommand {
public:
    PasteTextCommand() = default;
    void Apply(std::string& buffer, size_t& cursorPosition, std::string& clipboard, TextEditor& editor) override{
        if(!editor.HasSelection()){
            buffer=buffer.substr(0,cursorPosition)+clipboard+buffer.substr(cursorPosition, buffer.size());
            cursorPosition+=clipboard.size();
        }
        else{
            buffer=buffer.substr(0,editor.GetSelection().first)+clipboard+buffer.substr(editor.GetSelection().second,buffer.size());
            cursorPosition=editor.GetSelection().first;
            editor.UnselectText();

        }

    }
    void AcceptVisitor(CommandVisitor& visitor) override{
        visitor.VisitPasteTextCommand(*this);

    }
};

/* Привести выделенный текст в ВЕРХНИЙ регистр */
class UppercaseTextCommand : public ICommand {
public:
    UppercaseTextCommand() = default;
    void Apply(std::string& buffer, size_t& cursorPosition, std::string& clipboard, TextEditor& editor) override {
        if(editor.HasSelection()){
            for(size_t i = editor.GetSelection().first;i<=editor.GetSelection().second;i++)
                buffer[i]=std::toupper(buffer[i]);
        }
        if(editor.HasSelection())
            editor.UnselectText();
    }
    void AcceptVisitor(CommandVisitor& visitor) override{
        visitor.VisitUppercaseTextCommand(*this);
    }
};

/* Привести выделенный текст в нижний регистр */
class LowercaseTextCommand : public ICommand {
public:
    LowercaseTextCommand() = default;
    void Apply(std::string& buffer, size_t& cursorPosition, std::string& clipboard, TextEditor& editor) override {
        if(editor.HasSelection()){
            for(size_t i = editor.GetSelection().first;i<=editor.GetSelection().second;i++)
                buffer[i]=std::tolower(buffer[i]);
        }
        if(editor.HasSelection())
            editor.UnselectText();
    }
    void AcceptVisitor(CommandVisitor& visitor) override{
        visitor.VisitLowercaseTextCommand(*this);

    }

};

/* Перенести курсор в конец строки */
class MoveToEndCommand : public ICommand {
public:
    MoveToEndCommand() = default;

    void Apply(std::string& buffer, size_t& cursorPosition, std::string& clipboard, TextEditor& editor) override {
        while(buffer[cursorPosition]!='\n' and cursorPosition<buffer.size())
            cursorPosition +=1;
        if(buffer[cursorPosition]=='\n')
            cursorPosition+=1;
        if(editor.HasSelection())
            editor.UnselectText();
    }
    void AcceptVisitor(CommandVisitor& visitor) override{
        visitor.VisitMoveToEndCommand(*this);

    }

};

/* Перенести курсор в начало строки */
class MoveToStartCommand : public ICommand {
public:
    MoveToStartCommand() = default;
    void Apply(std::string& buffer, size_t& cursorPosition, std::string& clipboard, TextEditor& editor) override {
        if(cursorPosition>buffer.size()-1)
            cursorPosition=buffer.size()-1;
        while(buffer[cursorPosition]!='\n' and cursorPosition!=0){
            cursorPosition-=1;
        }
        if(cursorPosition!=0){
            cursorPosition+=1;}
        if(editor.HasSelection())
            editor.UnselectText();
    }
    void AcceptVisitor(CommandVisitor& visitor) override{
        visitor.VisitMoveToStartCommand(*this);
    }

};

/* Удалить часть строки, начиная от позиции курсора до первого пробела или конца строки */
class DeleteWordCommand : public ICommand {
public:
    DeleteWordCommand() =default;
    void Apply(std::string& buffer, size_t& cursorPosition, std::string& clipboard, TextEditor& editor) override {
        // else{
        size_t prev_cursorPosition=cursorPosition;
        while(buffer[cursorPosition]!=' ' and buffer[cursorPosition]!='\n'){
            cursorPosition+=1;
        }
        //cursorPosition-=1;
        buffer= buffer.substr(0,prev_cursorPosition)+buffer.substr(cursorPosition, buffer.size());
        cursorPosition=prev_cursorPosition;
        if(editor.HasSelection())
            editor.UnselectText();
    }
    void AcceptVisitor(CommandVisitor& visitor) override{
        visitor.VisitDeleteWordCommand(*this);
    }
};

/* Макрос */
class MacroCommand : public ICommand {
public:
    explicit MacroCommand(std::list<CommandPtr> subcommands):macro_(std::move(subcommands)){

    }
    void Apply(std::string& buffer, size_t& cursorPosition, std::string& clipboard, TextEditor& editor) override {
        for(const auto & i:macro_){

            i->Apply(buffer,cursorPosition,clipboard,editor);
        }
    }
    void AcceptVisitor(CommandVisitor& visitor) override{
        for(const auto & i: macro_){
            i->AcceptVisitor(visitor);
        }

    }

private:
    std::list<CommandPtr> macro_;





};
CommandBuilder::CommandBuilder() :logStreamPtr_(nullptr){}
CommandBuilder &CommandBuilder::Text(std::string text) {
    this->text_=std::move(text);
    return *this;
}

CommandBuilder &CommandBuilder::WithType(Type type) {
    this->type_=type;
    return *this;
}

CommandBuilder &CommandBuilder::SelectionSize(size_t selectionSize) {
    this->selectionSize_ = selectionSize;
    return *this;
}

CommandBuilder &CommandBuilder::AddSubcommand( CommandPtr subcommand) {
    this->subcommands_.push_back(subcommand);
    return *this;
}

CommandBuilder &CommandBuilder::LogTo(std::ostream &logStream) {
    logStreamPtr_ = &logStream;
    return *this;
}


CommandPtr CommandBuilder::build() {
    CommandPtr ptr;
    switch (this->type_) {
        case Type::InsertText:
            ptr= std::make_shared<InsertTextCommand>(InsertTextCommand(this->text_));
            break;
        case Type::MoveCursorLeft:
            ptr= std::make_shared<MoveCursorLeftCommand>(MoveCursorLeftCommand());
            break;
        case Type::MoveToEnd:
            ptr= std::make_shared<MoveToEndCommand>(MoveToEndCommand());
            break;
        case Type::MoveCursorUp:
            ptr= std::make_shared<MoveCursorUpCommand>(MoveCursorUpCommand());
            break;
        case Type::SelectText:
            ptr= std::make_shared<SelectTextCommand>(SelectTextCommand(this->selectionSize_));
            break;
        case Type::CopyText:
            ptr= std::make_shared<CopyTextCommand>(CopyTextCommand());
            break;
        case Type::PasteText:
            ptr= std::make_shared<PasteTextCommand>(PasteTextCommand());
            break;
        case Type::MoveToStart:
            ptr= std::make_shared<MoveToStartCommand>(MoveToStartCommand());
            break;
        case Type::Macro:
            ptr= std::make_shared<MacroCommand>(MacroCommand(this->subcommands_));
            break;
        case Type::DeleteWord:
            ptr= std::make_shared<DeleteWordCommand>(DeleteWordCommand());
            break;
        case Type::MoveCursorDown:
            ptr= std::make_shared<MoveCursorDownCommand>(MoveCursorDownCommand());
            break;
        case Type::LowercaseText:
            ptr= std::make_shared<LowercaseTextCommand>(LowercaseTextCommand());
            break;
        case Type::UppercaseText:
            ptr= std::make_shared<UppercaseTextCommand>(UppercaseTextCommand());
            break;
        case Type::DeleteText:
            ptr=std::make_shared<DeleteTextCommand>(DeleteTextCommand());
            break;
        case Type::MoveCursorRight:
            ptr=std::make_shared<MoveCursorRightCommand>(MoveCursorRightCommand());
            break;

    }
    if(logStreamPtr_!= nullptr){
        CommandPtr commandWrapper=std::make_shared<LoggedCommandWrapper>(LoggedCommandWrapper(*(this->logStreamPtr_),ptr));
        return commandWrapper;
    }
    else
        return ptr;
}