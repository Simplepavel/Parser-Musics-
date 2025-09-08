#include "parsers.hpp"

std::string Find::file_to_string(std::ifstream &file)
{
    std::string result;
    file.seekg(0, std::ios::end);
    int size = file.tellg();
    result.reserve(size);
    file.seekg(0, std::ios::beg);
    char t;
    while (file.peek() != EOF)
    {
        file.get(t);
        result.push_back(t);
    }
    return result;
}

void Find_Artists::find(GumboNode *node, std::set<std::string> &argv2)
{

    if (node->type != GUMBO_NODE_ELEMENT)
    {
        return;
    }
    GumboElement *elem = &node->v.element;
    if (elem->tag == GUMBO_TAG_A)
    {
        GumboVector *attrs = &elem->attributes;
        if (attrs->length == 2)
        {
            GumboAttribute *attr = static_cast<GumboAttribute *>(attrs->data[0]);
            std::string name = attr->name;
            std::string value = attr->value;
            if (name == "href" && value.find("/artist/") != std::string::npos)
            {
                argv2.insert(value.substr(8));
            }
        }
    }
    // продолжение обхода
    GumboVector *children = &elem->children;
    for (int i = 0; i < children->length; ++i)
    {
        GumboNode *child = static_cast<GumboNode *>(children->data[i]);
        find(child, argv2);
    }
}

std::set<std::string> &Find_Artists::parse(std::ifstream &file)
{
    std::string string_html = file_to_string(file);
    GumboOutput *root = gumbo_parse(string_html.c_str());
    find(root->root, result);
    return result;
}

void Find_Tracks::find_url_download(GumboElement *elem, Song &s)
{
    GumboVector *children = &elem->children;
    int i = 0;
    for (; i < children->length; ++i)
    {
        GumboNode *a = static_cast<GumboNode *>(children->data[i]);
        if (a->type == GUMBO_NODE_ELEMENT)
        {
            GumboElement *html_tag = &a->v.element;
            if (html_tag->tag == GUMBO_TAG_A)
            {
                GumboVector *attrs = &html_tag->attributes;
                GumboAttribute *url = static_cast<GumboAttribute *>(attrs->data[1]);
                s.download_url = url->value;
                return;
            }
        }
    }
}

void Find_Tracks::find_title_artist(GumboElement *elem, Song &s)
{
    GumboVector *children = &elem->children;
    std::vector<GumboNode *> element_children;
    element_children.reserve(2);
    for (int i = 0; i < children->length; ++i)
    {
        GumboNode *a = static_cast<GumboNode *>(children->data[i]);
        if (a->type == GUMBO_NODE_ELEMENT)
        {
            element_children.push_back(a);
        }
    }
    GumboElement *track_title = &element_children[0]->v.element;
    GumboVector *track_title_children = &track_title->children;
    for (int j = 0; j < track_title_children->length; ++j)
    {
        GumboNode *child = static_cast<GumboNode *>(track_title_children->data[j]);
        if (child->type == GUMBO_NODE_TEXT)
        {
            std::string title = child->v.text.text;
            remove_space(title);
            s.title = title;
            break;
        }
    }

    GumboElement *track_desc = &element_children[1]->v.element;
    GumboVector *track_title_desc = &track_desc->children;
    for (int k = 0; k < track_title_desc->length; ++k)
    {
        GumboNode *child = static_cast<GumboNode *>(track_title_desc->data[k]);
        if (child->type == GUMBO_NODE_TEXT)
        {
            std::string artist_title = child->v.text.text;
            remove_space(artist_title);
            s.artist_title = artist_title;
            break;
        }
    }
}

void Find_Tracks::find(GumboNode *node, std::vector<Song> &argv2)
{
    if (node->type != GUMBO_NODE_ELEMENT)
    {
        return;
    }
    GumboElement *elem = &node->v.element;
    if (elem->tag == GUMBO_TAG_DIV) // поиск info
    {
        GumboVector *attrs = &elem->attributes;
        if (attrs->length == 1)
        {
            GumboAttribute *attr = static_cast<GumboAttribute *>(attrs->data[0]);
            std::string name = attr->name;
            std::string value = attr->value;
            if (name == "class" && value == "track__info")
            {
                GumboVector *children = &elem->children;
                std::vector<GumboNode *> element_children;
                element_children.reserve(2);
                for (unsigned int i = 0; i < children->length; ++i)
                {
                    GumboNode *child = static_cast<GumboNode *>(children->data[i]);
                    if (child->type == GUMBO_NODE_ELEMENT)
                    {
                        element_children.push_back(child);
                    }
                }
                GumboElement *inner_a = &element_children[0]->v.element; // нашли названия треков
                GumboElement *inner_div = &element_children[1]->v.element;
                Song s;
                find_title_artist(inner_a, s);
                find_url_download(inner_div, s);
                argv2.push_back(s);
            }
        }
    }
    GumboVector *children = &elem->children;
    for (int i = 0; i < children->length; ++i)
    {
        GumboNode *child = static_cast<GumboNode *>(children->data[i]);
        find(child, argv2);
    }
}

std::vector<Song> &Find_Tracks::parse(std::ifstream &file)
{
    std::string string_html = file_to_string(file);
    GumboOutput *root = gumbo_parse(string_html.c_str());
    find(root->root, result);
    return result;
}
