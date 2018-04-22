#include "stdafx.h"
#include "CppUnitTest.h"
#include "../RestAPI/handler.h"
#include "../RestAPI/logger.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace RestAPITest
{		
	TEST_CLASS(UnitTest1)
	{
	public:
		
		/*merginf blobs test*/
		TEST_METHOD(post_merge)
		{
			handler h;
			h.post_merge(U("3"), U("jpg"));
			utility::ifstream_t ex("..\\container\\1\\img_example.jpg");
			if (!ex) std::cout << "error1";
			utility::ifstream_t merge("..\\container\\3\\merge.jpg");
			if (!merge) std::cout << "error2";
			utility::string_t ex_line, merge_line;
			//compare with example img
			while (getline(ex, ex_line) && getline(merge, merge_line)) {

				Assert::AreEqual(ex_line, merge_line);
			}
			ex.close();
			merge.close();
		}

		/*container test*/
		TEST_METHOD(post_container) {
			handler h;
			h.post_container(U("4"));

			WIN32_FIND_DATA FindFileData;
			HANDLE hf;
			hf = FindFirstFile(U("..\\container\\4"), &FindFileData);
			/*if this container exists*/
			Assert::IsFalse(hf == INVALID_HANDLE_VALUE);
			FindClose(hf);

		}

		/*blob test*/
		TEST_METHOD(post_blob) {
			handler h;
			utility::string_t test_string = U("test_blob_data");
			h.post_blob(U("4"), U("1"), test_string);
			utility::ifstream_t blob("..\\container\\4\\1.blob");
			utility::string_t blob_line;
			//compare with example string
			getline(blob, blob_line);
			Assert::AreEqual(blob_line, test_string);
			blob.close();
		}

		/*delete container test*/
		TEST_METHOD(delete_container) {
			handler h;
			h.delete_container(U("4"));

			WIN32_FIND_DATA FindFileData;
			HANDLE hf;
			hf = FindFirstFile(U("..\\container\\4"), &FindFileData);
			/*if this container exists*/
			Assert::IsTrue(hf == INVALID_HANDLE_VALUE);
			FindClose(hf);
		}

	};
}