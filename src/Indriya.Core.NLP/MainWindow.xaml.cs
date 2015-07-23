using System;
using System.IO;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Documents;
using edu.stanford.nlp.pipeline;
using java.io;

namespace Indriya.Core.NLP
{
    /// <summary>
    /// Interaction logic for MainWindow.xaml
    /// </summary>
    public partial class MainWindow : Window
    {
        private StanfordCoreNLP _pipeline;
        private readonly Task<bool> _task1;

        public MainWindow()
        {
            InitializeComponent();
            _task1 = Task<bool>.Factory.StartNew(Init);
        }

        private bool Init()
        {
            if (_pipeline == null)
            {
                Application.Current.Dispatcher.Invoke(() =>
                {
                    StatusBarText.Text = "Initializing Stanford Core NLP...";
                });
                // Path to the folder with models extracted from `stanford-corenlp-3.5.1-models.jar`
                //var jarRoot = @"c:\models\stanford-corenlp-full-2015-01-30\stanford-corenlp-3.5.1-models\";
                const string jarRoot =
                    @"C:\Work\Develop\tools\NLP\stanford-corenlp-full-2015-01-29\stanford-corenlp-3.5.1-models\";

                // Annotation pipeline configuration
                var props = new java.util.Properties();
                props.setProperty("annotators", "tokenize, ssplit, pos, lemma, ner, parse, dcoref");
                props.setProperty("sutime.binders", "0");

                // We should change current directory, so StanfordCoreNLP could find all the model files automatically 
                var curDir = Environment.CurrentDirectory;
                Directory.SetCurrentDirectory(jarRoot);
                _pipeline = new StanfordCoreNLP(props);
                Directory.SetCurrentDirectory(curDir);
                Application.Current.Dispatcher.Invoke(() =>
                {
                    StatusBarText.Text = "Completed initialization of Stanford Core NLP...";
                });
                return true;
            }
            return false;
        }

        private void Button_Click(object sender, RoutedEventArgs e)
        {
            var text = "Kosgi Santosh sent an email to Stanford University. He didn&#39;t get a reply.";
            if (InputTextBox.Document != null)
            {
                TextRange textRange = new TextRange(InputTextBox.Document.ContentStart,
                    InputTextBox.Document.ContentEnd);
                text = textRange.Text;
            }
            if (_task1 != null && _task1.IsCompleted && !string.IsNullOrEmpty(text))
            {
                // Text for processing
                //var text = "Kosgi Santosh sent an email to Stanford University. He didn&#39;t get a reply.";
                //if (InputTextBox.Document != null)
                //{
                //    text = InputTextBox.Document.ToString();
                //}
                // Annotation
                var annotation = new Annotation(text);
                _pipeline.annotate(annotation);

                // Result - Pretty Print
                using (var stream = new ByteArrayOutputStream())
                {
                    _pipeline.prettyPrint(annotation, new PrintWriter(stream));
                    OutputTextBox.Document.Blocks.Clear();
                    OutputTextBox.AppendText(stream.toString());
                    stream.close();
                }
            }
        }
    }
}
