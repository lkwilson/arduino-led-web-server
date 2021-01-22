struct Page {
  const char* const filename;
  const char* const content;
};

WEB_SERVER_DECL_HOOKS

Page pages[] = {
WEB_SERVER_PAGE_HOOKS
};
