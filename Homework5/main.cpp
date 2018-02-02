#include "header.h"
#include <memory>
class GraphicEditor
{
private:
    std::unique_ptr<Document> doc;
public:
    void createDocument()
    {
        doc.reset(new Document());
    }

    void importDocument(const std::string& filename)
    {
        doc.reset(new Document(filename));
    }

    void exportDocument(const std::string& filename)
    {
        doc->exportInFile(filename);
    }

    void addElement(GraphicElement* element)
    {
        doc->createElement(element);
    }

    void removeElement(GraphicElement* element)
    {
        doc->removeElement(element);
    }
};

int main()
{
    GraphicEditor editor;
    std::unique_ptr<Triangle> triangle(new Triangle);
    std::unique_ptr<Square> square(new Square);
    std::unique_ptr<Line> line(new Line);
    editor.createDocument();
    editor.addElement(triangle.get());
    editor.addElement(square.get());
    editor.addElement(line.get());

    editor.exportDocument("filename1");
    return 0;
}


