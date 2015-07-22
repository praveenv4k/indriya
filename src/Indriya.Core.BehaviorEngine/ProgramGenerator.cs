using System.Collections.Generic;
using System.IO;
using System.Text;

namespace Indriya.Core.BehaviorEngine
{
    public class ProgramGenerator
    {
        private const string ModifyText = "<% MODIFY_HERE %>";

        public static void GeneratePrograms(IDictionary<string, string> gestureBehaviorMap, string path)
        {
            using (var stream = new MemoryStream(Properties.Resources.main_template))
            using (var reader = new StreamReader(stream))
            {
                string result = reader.ReadToEnd();

                var stringBuilder = new StringBuilder();
                foreach (var item in gestureBehaviorMap)
                {
                    stringBuilder.AppendLine("gestBehaviorMap.Add(\"" + item.Key + "\"" + ", \"" + item.Value +
                                             "\");");
                }
                var newFile = result.Replace(ModifyText, stringBuilder.ToString());
                File.WriteAllText(path, newFile);
            }
        }

        public static void GeneratePrograms(string jsonString, string path)
        {
            using (var stream = new MemoryStream(Properties.Resources.main_template))
            using (var reader = new StreamReader(stream))
            {
                string result = reader.ReadToEnd();
                var newFile = result.Replace(ModifyText, jsonString);
                File.WriteAllText(path, newFile);
            }
        }
    }
}