using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Text.RegularExpressions;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Navigation;
using System.Windows.Shapes;
using Nancy.Hosting.Self;

namespace NancyFx
{
    /// <summary>
    /// Interaction logic for MainWindow.xaml
    /// </summary>
    public partial class MainWindow : Window
    {
        private Nancy.Hosting.Self.NancyHost _host;

        public MainWindow()
        {
            InitializeComponent();
            Loaded += (sender, args) =>
            {
                _host = new NancyHost(new Uri("http://localhost:8888/"), new WebBootStrapper());
                _host.Start();
            };
            Closing += (sender, args) =>
            {
                _host.Stop();
                _host.Dispose();
                _host = null;
            };

            string txt = "/models/collada/nao.dae";

            string re1 = "(\\/)";	// Any Single Character 1
            string re2 = "(models)";	// Word 1
            string re3 = "(\\/)";	// Any Single Character 2

            Regex r = new Regex(re1 + re2 + re3, RegexOptions.IgnoreCase | RegexOptions.Singleline);
            Match m = r.Match(txt);
            if (m.Success)
            {
                String c1 = m.Groups[1].ToString();
                String word1 = m.Groups[2].ToString();
                String c2 = m.Groups[3].ToString();
                Console.Write("(" + c1.ToString() + ")" + "(" + word1.ToString() + ")" + "(" + c2.ToString() + ")" + "\n");
            }
        }
    }
}