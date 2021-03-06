#include "svgsymbolelement.h"
#include "rendercontext.h"

namespace lunasvg {

SVGSymbolElement::SVGSymbolElement(SVGDocument* document) :
    SVGStyledElement(ElementIdSymbol, document),
    SVGFitToViewBox(this)
{
}

void SVGSymbolElement::render(RenderContext& context) const
{
    if(context.state().element->elementId() != ElementIdUse || style().isDisplayNone())
    {
        context.skipElement();
        return;
    }

    const RenderState& state = context.state();
    const Rect& viewPort = state.viewPort;

    SVGStyledElement::render(context);
    RenderState& newState = context.state();
    newState.matrix.multiply(calculateViewBoxTransform(viewPort));
    newState.viewPort = viewBox().isSpecified() && viewBox().property()->isValid() ? viewBox().property()->value() : viewPort;
}

SVGElementImpl* SVGSymbolElement::clone(SVGDocument* document) const
{
    SVGSymbolElement* e = new SVGSymbolElement(document);
    baseClone(*e);
    return  e;
}

} // namespace lunasvg
