// Copyright © 2010-2014 The CefSharp Authors. All rights reserved.
//
// Use of this source code is governed by a BSD-style license that can be found in the LICENSE file.

using System;
using System.ComponentModel;
using System.Windows;
using System.Windows.Input;
using CefSharp;
using CefSharp.Wpf;

namespace Indriya.Application.Mvvm
{
    public class BrowserTabViewModel : INotifyPropertyChanged
    //public class BrowserTabViewModel : ViewModelBase
    {
        private string _address;

        public string Address
        {
            get { return _address; }
            set { PropertyChanged.ChangeAndNotify(ref _address, value, () => Address); }
        }

        private string _addressEditable;

        public string AddressEditable
        {
            get { return _addressEditable; }
            set { PropertyChanged.ChangeAndNotify(ref _addressEditable, value, () => AddressEditable); }
        }

        private string _outputMessage;

        public string OutputMessage
        {
            get { return _outputMessage; }
            set { PropertyChanged.ChangeAndNotify(ref _outputMessage, value, () => OutputMessage); }
        }

        private string _statusMessage;

        public string StatusMessage
        {
            get { return _statusMessage; }
            set { PropertyChanged.ChangeAndNotify(ref _statusMessage, value, () => StatusMessage); }
        }

        private string _title;

        public string Title
        {
            get { return _title; }
            set { PropertyChanged.ChangeAndNotify(ref _title, value, () => Title); }
        }

        private IWpfWebBrowser _webBrowser;

        public IWpfWebBrowser WebBrowser
        {
            get { return _webBrowser; }
            set { PropertyChanged.ChangeAndNotify(ref _webBrowser, value, () => WebBrowser); }
        }

        private object _evaluateJavaScriptResult;

        public object EvaluateJavaScriptResult
        {
            get { return _evaluateJavaScriptResult; }
            set
            {
                PropertyChanged.ChangeAndNotify(ref _evaluateJavaScriptResult, value, () => EvaluateJavaScriptResult);
            }
        }

        private bool _showSidebar;

        public bool ShowSidebar
        {
            get { return _showSidebar; }
            set { PropertyChanged.ChangeAndNotify(ref _showSidebar, value, () => ShowSidebar); }
        }

        public ICommand GoCommand { get; set; }
        public ICommand HomeCommand { get; set; }
        public ICommand ExecuteJavaScriptCommand { get; set; }
        public ICommand EvaluateJavaScriptCommand { get; set; }

        public event PropertyChangedEventHandler PropertyChanged;

        public BrowserTabViewModel(string address)
        {
            Address = address;
            AddressEditable = Address;

            GoCommand = new DelegateCommand(Go, () => !String.IsNullOrWhiteSpace(Address));
            HomeCommand = new DelegateCommand(() => AddressEditable = Address = "http://localhost:8888");
            ExecuteJavaScriptCommand = new DelegateCommand<string>(ExecuteJavaScript, s => !String.IsNullOrWhiteSpace(s));
            EvaluateJavaScriptCommand = new DelegateCommand<string>(EvaluateJavaScript,
                s => !String.IsNullOrWhiteSpace(s));

            PropertyChanged += OnPropertyChanged;

            var version = String.Format("Chromium: {0}, CEF: {1}, CefSharp: {2}", Cef.ChromiumVersion, Cef.CefVersion,
                Cef.CefSharpVersion);
            OutputMessage = version;
        }

        private async void EvaluateJavaScript(string s)
        {
            try
            {
                var response = await _webBrowser.EvaluateScriptAsync(s);
                if (response.Success && response.Result is IJavascriptCallback)
                {
                    response =
                        await
                            ((IJavascriptCallback) response.Result).ExecuteAsync(
                                "This is a callback from EvaluateJavaScript");
                }

                EvaluateJavaScriptResult = response.Success ? (response.Result ?? "null") : response.Message;
            }
            catch (Exception e)
            {
                MessageBox.Show("Error while evaluating Javascript: " + e.Message, "Error", MessageBoxButton.OK,
                    MessageBoxImage.Error);
            }
        }

        private void ExecuteJavaScript(string s)
        {
            try
            {
                _webBrowser.ExecuteScriptAsync(s);
            }
            catch (Exception e)
            {
                MessageBox.Show("Error while executing Javascript: " + e.Message, "Error", MessageBoxButton.OK,
                    MessageBoxImage.Error);
            }
        }

        private void OnPropertyChanged(object sender, PropertyChangedEventArgs e)
        {
            switch (e.PropertyName)
            {
                case "Address":
                    AddressEditable = Address;
                    break;

                case "WebBrowser":
                    if (WebBrowser != null)
                    {
                        WebBrowser.ConsoleMessage += OnWebBrowserConsoleMessage;
                        WebBrowser.StatusMessage += OnWebBrowserStatusMessage;
                        WebBrowser.LoadError += OnWebBrowserLoadError;

                        // TODO: This is a bit of a hack. It would be nicer/cleaner to give the webBrowser focus in the Go()
                        // TODO: method, but it seems like "something" gets messed up (= doesn't work correctly) if we give it
                        // TODO: focus "too early" in the loading process...
                        WebBrowser.FrameLoadEnd +=
                            delegate
                            {
                                System.Windows.Application.Current.Dispatcher.BeginInvoke((Action) (() => _webBrowser.Focus()));
                            };
                    }

                    break;
            }
        }

        private void OnWebBrowserConsoleMessage(object sender, ConsoleMessageEventArgs e)
        {
            OutputMessage = e.Message;
        }

        private void OnWebBrowserStatusMessage(object sender, StatusMessageEventArgs e)
        {
            StatusMessage = e.Value;
        }

        private void OnWebBrowserLoadError(object sender, LoadErrorEventArgs args)
        {
            // Don't display an error for downloaded files where the user aborted the download.
            if (args.ErrorCode == CefErrorCode.Aborted)
                return;

            var errorMessage = "<html><body><h2>Failed to load URL " + args.FailedUrl +
                               " with error " + args.ErrorText + " (" + args.ErrorCode +
                               ").</h2></body></html>";

            _webBrowser.LoadHtml(errorMessage, args.FailedUrl);
        }

        private void Go()
        {
            Address = AddressEditable;

            // Part of the Focus hack further described in the OnPropertyChanged() method...
            Keyboard.ClearFocus();
        }

        #region ContentId

        private string _contentId = null;
        public string ContentId
        {
            get { return _contentId; }
            set { PropertyChanged.ChangeAndNotify(ref _contentId, value, () => ContentId); }
        }

        #endregion

        #region IsSelected

        private bool _isSelected = true;
        public bool IsSelected
        {
            get { return _isSelected; }
            set { PropertyChanged.ChangeAndNotify(ref _isSelected, value, () => IsSelected); }
        }

        #endregion

        #region IsActive

        private bool _isActive = true;
        public bool IsActive
        {
            get { return _isActive; }
            set { PropertyChanged.ChangeAndNotify(ref _isActive, value, () => IsActive); }
        }

        #endregion
    }
}