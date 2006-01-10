/*
 * This file is part of the DOM implementation for KDE.
 *
 * Copyright (C) 1999 Lars Knoll (knoll@kde.org)
 *           (C) 1999 Antti Koivisto (koivisto@kde.org)
 *           (C) 2000 Dirk Mueller (mueller@kde.org)
 * Copyright (C) 2004, 2005, 2006 Apple Computer, Inc.
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Library General Public
 * License as published by the Free Software Foundation; either
 * version 2 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Library General Public License for more details.
 *
 * You should have received a copy of the GNU Library General Public License
 * along with this library; see the file COPYING.LIB.  If not, write to
 * the Free Software Foundation, Inc., 59 Temple Place - Suite 330,
 * Boston, MA 02111-1307, USA.
 *
 */
#ifndef HTML_HTMLGenericFormElementImpl_h
#define HTML_HTMLGenericFormElementImpl_h

#include "html/html_elementimpl.h"

namespace khtml {
    class RenderFormElement;
}

namespace DOM {

class FormDataList;
class HTMLFormElementImpl;

class HTMLGenericFormElementImpl : public HTMLElementImpl
{
    friend class HTMLFormElementImpl;
    friend class khtml::RenderFormElement;

public:
    HTMLGenericFormElementImpl(const QualifiedName& tagName, DocumentImpl *doc, HTMLFormElementImpl *f = 0);
    virtual ~HTMLGenericFormElementImpl();

    virtual HTMLTagStatus endTagRequirement() const { return TagStatusRequired; }
    virtual int tagPriority() const { return 1; }

    HTMLFormElementImpl *form() { return m_form; }

    virtual DOMString type() const = 0;

    virtual bool isControl() const { return true; }
    virtual bool isEnabled() const { return !disabled(); }

    virtual void parseMappedAttribute(MappedAttributeImpl *attr);
    virtual void attach();
    virtual void insertedIntoTree(bool deep);
    virtual void removedFromTree(bool deep);

    virtual void reset() {}

    void onSelect();
    void onChange();

    bool disabled() const;
    void setDisabled(bool _disabled);

    virtual bool isFocusable() const;
    virtual bool isKeyboardFocusable() const;
    virtual bool isMouseFocusable() const;
    virtual bool isEnumeratable() const { return false; }

    bool readOnly() const { return m_readOnly; }
    void setReadOnly(bool _readOnly);

    virtual void recalcStyle( StyleChange );

    virtual DOMString name() const;
    void setName(const DOMString& name);

    virtual bool isGenericFormElement() const { return true; }
    virtual bool isRadioButton() const { return false; }

    /*
     * override in derived classes to get the encoded name=value pair
     * for submitting
     * return true for a successful control (see HTML4-17.13.2)
     */
    virtual bool appendFormData(FormDataList&, bool) { return false; }

    virtual bool isEditable();

    virtual QString state();
    QString findMatchingState(QStringList &states);

    virtual bool isSuccessfulSubmitButton() const { return false; }
    virtual bool isActivatedSubmit() const { return false; }
    virtual void setActivatedSubmit(bool flag) { }

    int tabIndex() const;
    void setTabIndex(int);

protected:
    HTMLFormElementImpl *getForm() const;

    HTMLFormElementImpl *m_form;
    bool m_disabled : 1;
    bool m_readOnly: 1;
    bool m_inited : 1;
};

} //namespace

#endif
