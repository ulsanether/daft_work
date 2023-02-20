using System;
using System.Drawing;
using System.Drawing.Imaging;
using System.IO;
using System.Runtime.InteropServices;
using System.Text;
using System.Windows.Forms;
using Kbg.NppPluginNET.PluginInfrastructure;

namespace Kbg.NppPluginNET
{
    class Main
    {
        internal const string PluginName = "WordPadPlusPlus";

        static INotepadPPGateway notepad = new NotepadPPGateway();
        static IScintillaGateway editor = new ScintillaGateway(PluginBase.GetCurrentScintilla());
        static internal void CommandMenuInit()
        {
           
            StringBuilder sbIniFilePath = new StringBuilder(Win32.MAX_PATH);
            Win32.SendMessage(PluginBase.nppData._nppHandle, (uint)NppMsg.NPPM_GETPLUGINSCONFIGDIR, Win32.MAX_PATH, sbIniFilePath);
            PluginBase.SetCommand(0, "WordPad++ NewFile", newFile);
            PluginBase.SetCommand(1, "Main Label", SetMain, new ShortcutKey(false, false, false, Keys.None));
			 PluginBase.SetCommand(2, "&About WordPad++", ShowAbout, new ShortcutKey(false, false, false, Keys.None));
        }

        static void newFile()
        {
            notepad.FileNew();
            editor.WordRight();
            editor.ReplaceSel($@"WordPad++ set C-Languge.
");
            string dateTime = string.Format("{0} {1} \n\n\n", DateTime.Now.ToShortTimeString(), DateTime.Now.ToShortDateString());
            editor.ReplaceSel(dateTime);
        }



		static void SetMain(){

            editor.ReplaceSel("[1]");  //line number base 


        }
		
		
        static void insertDateTime(bool longFormat)
        {
            string dateTime = string.Format("{0} {1}", DateTime.Now.ToShortTimeString(), longFormat ? DateTime.Now.ToLongDateString() : DateTime.Now.ToShortDateString());
            editor.ReplaceSel(dateTime);
  
        }

        private static void ShowAbout()
        {
            var message = @"Version: 0.1
License: This is freeware (Apache v2.0 license).
Author: DaftWork
Website:https://github.com/ulsanether?tab=repositories";
            var title = "WordPadPlusPlus plugin";
            MessageBox.Show(message, title, MessageBoxButtons.OK);
        }
    }
}