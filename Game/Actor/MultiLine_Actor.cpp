#include "MultiLine_Actor.h"
#include "Utils/Utils.h"
MultiLine_Actor::MultiLine_Actor(const char* filePath, Color color,
	const Vector2& position)
	: Actor("", color, position)
{
	FILE* file = nullptr;
	fopen_s(&file, filePath, "rt");

	if (file == nullptr)
	{
		std::cout << "FatalError : Can not Read File\n";
		__debugbreak;
		return;
	}

	char buffer[4000] = {};

	while (fgets(buffer, sizeof(buffer), file))
	{
		size_t length = strlen(buffer);

		if (length > 0 && (buffer[length -1] == '\n') ||
			buffer[length - 1] == '\r')
		{
			buffer[length] = '\0';
			if (length > 1 && buffer[length - 2] == '\r')
				buffer[length - 2] = '\0';
		}

		lines.emplace_back(buffer);
	}
	fclose(file);
}

void MultiLine_Actor::Render()
{
	Utils::SetConsoleTextColor(color);

	Vector2 pos = GetActorPosition();

	for (size_t i = 0; i < lines.size(); ++i)
	{
		Utils::SetConsolePosition(Vector2(pos.x, pos.y + static_cast<int>(i)));
		std::cout << lines[i];
	}
}
