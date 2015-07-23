using System;
using System.Collections.Generic;
using System.Linq;
using System.Xml;
using System.Xml.Linq;

namespace Indriya.Core.Util
{
    public static class LinqXmlExtensions
    {
        //public static IEnumerable<XElement> ElementsAnyNamespace<T>(this IEnumerable<T> source, string localName)
        //    where T : XContainer
        //{
        //    return source.Elements().Where(e => e.Name.LocalName == localName);
        //}

        public static XAttribute AttributeAnyNs<T>(this T source, string localName)
            where T : XElement
        {
            return source.Attributes().SingleOrDefault(e => e.Name.LocalName == localName);
        }

        public static IEnumerable<XElement> ElementsAnyNs<T>(this IEnumerable<T> source, string localName)
            where T : XContainer
        {
            return source.Elements().Where(e => e.Name.LocalName == localName);
        }

        public static IEnumerable<XElement> ElementsAnyNs<T>(this T source, string localName)
            where T : XContainer
        {
            return source.Elements().Where(e => e.Name.LocalName == localName);
        }
    }

    public static class XmlDocumentUtil
    {
        public static XmlDocument RemoveXmlns(XmlDocument doc)
        {
            XDocument d;
            using (var nodeReader = new XmlNodeReader(doc))
                d = XDocument.Load(nodeReader);

            if (d.Root != null) d.Root.Descendants().Attributes().Where(x => x.IsNamespaceDeclaration).Remove();

            foreach (var elem in d.Descendants())
                elem.Name = elem.Name.LocalName;

            var xmlDocument = new XmlDocument();
            using (var xmlReader = d.CreateReader())
                xmlDocument.Load(xmlReader);

            return xmlDocument;
        }

        public static XmlDocument RemoveXmlns(String xml)
        {
            XDocument d = XDocument.Parse(xml);
            if (d.Root != null) d.Root.Descendants().Attributes().Where(x => x.IsNamespaceDeclaration).Remove();

            foreach (var elem in d.Descendants())
                elem.Name = elem.Name.LocalName;

            var xmlDocument = new XmlDocument();
            xmlDocument.Load(d.CreateReader());

            return xmlDocument;
        }
    }
}